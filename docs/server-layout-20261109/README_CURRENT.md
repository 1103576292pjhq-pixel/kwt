# kwt-soc ��ǰ�������

�������ڣ�2026-11-09������˵��������Ŀ¼���������ڣ������������ۺϡ����Ļ���ǩ�ˡ�

## Ŀ¼��;

| ·�� | ��; |
|---|---|
| e203/ | CPU ��Ƽ�ƽ̨���ϣ�����ԭλ |
| accelerator/ | �������� DMA ��ƣ�RTL λ�� rtl/ |
| shared_sram_bundle_01/ | ���� SRAM ��� |
| kwt_dma_soc_top.v | SoC ���� |
| sources.f | SoC ��ѡԴ�嵥���� dc/scripts/read_soc_design.py ��ȡ������ԭλ |
| test_env/ | SoC ��������������Ի������������ݼ�˵�� |
| tools/maintenance/legacy/ | ��ʷ�����ű�����·������ʧЧ����ֱ��ִ�� |
| manifests/ | �汾���ļ��嵥����ʷ��Ƽ�¼ |
| verification/history/ | ����֤���̡�Ŀ¼������¼�����ĵ����� |

·���Ա�Ŀ¼Ϊ��׼�����������̸�Ŀ¼Ϊ `/storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc`���ۺϺ͹��Ĺ�����Ϊͬһ Desktop �µ� `dc/`��

## ��ǰ���

- SoC ASIC ���ܷ��棺�� [SoC ʹ��˵��](test_env/soc_asic/README.md)����ǰ���Ϊ `test_env/soc_asic/scripts/run_asic_current.py`��
- ���� DMA ���������Լ����Ѻ�½��룺�� [������˵��](test_env/accelerator_dma/README.md)��DUT ������ `kwt_dma_accelerator`��
- �嵥���ۺϱ߽缰���죺�� [��ǰ�����뽻��˵��](test_env/docs/CURRENT_FLOW.md)��

## sources.f ��׼ȷ��λ

��Ŀ¼ sources.f ���ļ�������Ŀ¼�������� CANDIDATE ONLY��·�����ڲ����� ASIC �����á�SRAM �󶨺�ʱ�������֤����鷢�� dc/scripts/read_soc_design.py ֱ�Ӷ�ȡ���ļ������Ա���ԭλ���������ƶ���ɾ����

��ǰ ASIC ����ʹ�� test_env/soc_asic/config/sources-asic.f��ʵ����ʷ�ۺ����λ�� dc/runs/soc-romfix-synth-jlkfngx9/elab/read.tcl����������б�����Ϳ����ö�ȡ��ơ��������嵥���ܻ�����TB ����������ۺϡ�

## ������֤��Χ

�����ļ�����ʱ 1085 ������ļ�����δ�䡢256 ����ǰ ASIC ����У��ͨ��������֤Ŀ¼�ѹ鵵�� verification/history/legacy-real12-*/real12_verify_01���鵵��ǰ ASIC ��������ͨ����61 ���� fixture �ļ�����ʽ��������Ŀ¼һ�¡�

��ʷ 12 ��������֤�뱾�ֵ������������ֿ���¼������δ�����ۺϡ�δ���²⹦�ġ�δ��֤����ʵ������/SDF��Ŀ¼�����в����� GitHub ��ͬ����
