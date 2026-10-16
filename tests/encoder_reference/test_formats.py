import tempfile
from pathlib import Path
import sys
import unittest
import numpy as np

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from numeric.encoder.contracts import layout,write_array,sha
from numeric.encoder.verify_bundle import read_array


class FormatTests(unittest.TestCase):
    def test_full_offsets(self):
        got={e['name']:e['offset_words'] for e in layout()}
        self.assertEqual(got,{'wq':0,'wk':4096,'wv':8192,'wo':12288,'bo':16384,
                              'ln1_gamma':16448,'ln1_beta':16512,'w1':16576,'b1':32960,
                              'w2':33216,'b2':49600,'ln2_gamma':49664,'ln2_beta':49728})
        self.assertEqual(sum(e['words'] for e in layout()),49792)

    def test_hex_raw_sign_and_endian(self):
        with tempfile.TemporaryDirectory() as tmp:
            root=Path(tmp).resolve()
            values=np.array([0.,-0.,1.,-2.,np.nextafter(np.float32(0),np.float32(1))],np.float32)
            meta=write_array(root,'test',values)
            self.assertEqual((root/'test.hex').read_text(encoding='ascii').splitlines(),
                             ['00000000','80000000','3f800000','c0000000','00000001'])
            np.testing.assert_array_equal(read_array(root,meta).view(np.uint32),values.view(np.uint32))

    def test_fresh_hash_cannot_hide_hex_corruption(self):
        with tempfile.TemporaryDirectory() as tmp:
            root=Path(tmp).resolve();meta=write_array(root,'test',np.array([1.],np.float32))
            (root/'test.hex').write_text('3f800001\n',encoding='ascii')
            meta['hex_sha256']=sha(root/'test.hex')
            with self.assertRaisesRegex(ValueError,'hex disagrees'):
                read_array(root,meta)

    def test_array_nonfinite_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            for value in (float('inf'),float('-inf'),float('nan')):
                with self.assertRaisesRegex(ValueError,'nonfinite'):
                    write_array(Path(tmp),'test',np.array([value],np.float32))

if __name__=='__main__':unittest.main()
