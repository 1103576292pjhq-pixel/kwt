"""Contest-formula helpers, not official evaluator or official-data acceptance.

NRMSE arguments are FRACTIONS (0.03 = 3%), not percentage-point numbers.
Top-1 uses counts, so the two-percentage-point boundary is checked exactly.
"""
from __future__ import annotations
from fractions import Fraction
import argparse, json, math
from pathlib import Path


def finite(x: object) -> float:
    if isinstance(x,bool) or not isinstance(x,(int,float)) or not math.isfinite(x):
        raise ValueError('expected finite real value')
    return float(x)


def precision_points(nrmse_fraction: float) -> dict:
    r=finite(nrmse_fraction)
    if r<0:raise ValueError('negative error')
    return {'nrmse_fraction':r,'nrmse_percent':r*100,
            'numerical_threshold_pass':r<=0.03,
            'precision_points_out_of_10':max(0.0,10.0-r/0.003),
            'scope':'FORMULA_ONLY_NOT_OFFICIAL_GRADE'}


def aggregate_layer(pairs: list[tuple[list,list]]) -> dict:
    if not pairs:raise ValueError('empty sample collection')
    count=0;errors=[];energies=[]
    for ref,estimate in pairs:
        if not ref or len(ref)!=len(estimate):raise ValueError('empty/mismatched sample')
        r=[finite(v) for v in ref]; e=[finite(v) for v in estimate]
        try:
            errors.append(math.fsum((a-b)**2 for a,b in zip(r,e)))
            energies.append(math.fsum(a*a for a in r))
        except OverflowError as exc:
            raise ValueError('metric overflow') from exc
        count+=len(r)
    mse=math.fsum(errors)/count;ref_mse=math.fsum(energies)/count
    if not math.isfinite(mse) or not math.isfinite(ref_mse):raise ValueError('metric overflow')
    ratio=math.sqrt(mse)/max(math.sqrt(ref_mse),1e-8)
    return {'element_count':count,'sample_count':len(pairs),
            **precision_points(ratio)}


def top1_report(ref_correct: int,candidate_correct: int,total: int) -> dict:
    if any(type(v) is not int for v in (ref_correct,candidate_correct,total)):
        raise ValueError('counts must be integers')
    if total<=0 or not 0<=ref_correct<=total or not 0<=candidate_correct<=total:
        raise ValueError('invalid correct/total counts')
    drop=Fraction((ref_correct-candidate_correct)*100,total)
    points=min(Fraction(10),max(Fraction(0),10-drop/Fraction(1,5)))
    return {'drop_percentage_points':float(drop),'threshold_pass':drop<=2,
            'precision_points_out_of_10':float(points),
            'scope':'SAME_DATA_AND_CLASSIFIER_REQUIRED_NOT_OFFICIAL_GRADE'}


def demo() -> dict:
    return {'scope':'SYNTHETIC_METRIC_EXAMPLES',
            'ffn1':[precision_points(v) for v in (0,.000934224880,.003,.01,.02,.03,.031)],
            'top1':[top1_report(570,c,600) for c in (570,569,564,558,557)],
            'aggregate_energy_example':aggregate_layer([([1.0],[1.1]),([100.0],[100.0])])}


def main()->int:
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--out',type=Path,help='New report directory')
    a=p.parse_args()
    try:
        obj=demo();print(json.dumps(obj,ensure_ascii=False,indent=2))
        if a.out:
            a.out.mkdir(parents=True,exist_ok=False)
            (a.out/'precision_examples.json').write_text(json.dumps(obj,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
        return 0
    except (ValueError,OSError) as exc:p.error(str(exc));return 2
if __name__=='__main__':raise SystemExit(main())
