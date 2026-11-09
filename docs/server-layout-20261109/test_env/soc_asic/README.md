# SoC ASIC ��ǰ���ܷ���

�������ڣ�2026-11-09��

## ��ǰ���з�ʽ

�ڷ������ն�ִ�У������� Bash��

```text
cd /storage1/2026contest/server2/s2_21usr/Desktop/e203-integration/kwt-soc
python3 test_env/soc_asic/scripts/run_asic_current.py --tasks 1
```

���� 12 ������������Ϊ `--tasks 12`��Ĭ�ϸ��������е���ʷ simv �����й̼������н���½��� Desktop/dc/runs/asic-classified-*�����Ḳ����ʷ���н����

��Ҫ���±������ɼ� `--recompile`����ѡ����� VCS��**�����±��� CPU �̼�**������Ŀ¼������֤ʹ��Ĭ�ϸ��÷�ʽ��û����֤����������±������̡�

## ���ú��ļ�

- config/asic-current.json������У��ֵ��ִ�г��򡢱���������̼�������·����
- config/sources-asic.f��ASIC ����Դ�ļ��嵥�����ܰ��� TB �ͷ���ģ�ͣ����Ǵ��ۺ��嵥��
- config/fixture-identity.json����������У�顣
- config/ROM1KX32_verilog.rcf����ǰ���� ROM ���ݡ�
- scripts/run_asic_current.py����ǰ��ʽ���ܷ�����ڡ�
- scripts/audit_helpers/������ڵ������ƺ�������Ҫִ�о� FPGA main��
- firmware/������ CPU ����Դ�ļ���build/firmware_current/�����й̼��������
- tb/��platform/��monitors/������ƽ̨������ļ���platform/frozen_sources/ ������ʷ����Դ��ԭ�ֽڸ�����
- ../common/fixtures/ffn1-real12/����ǰ 12 ��ԭʼ�������ݡ�

�����в�����������ʷģ�壬ʵ��ִ��ʱ�� run_asic_current.py �滻�̼�������Ŀ¼�Ȳ��������ܰ� JSON �е�ģ������ԭ������ִ�С�

## ��֤������

Ŀ��ʱ�� 150 MHz����ǰ���ܷ������� ARM_UD_MODEL��δ���� FPGA �ꣻ�� +notimingcheck����˲����� SDF ʱ��ǩ�ˡ�

������ʷ ASIC ROM ������ 12 ������ͨ����¼�����ֹ鵵��Ŀ¼��1 ����ͨ��������� 25344����ǰ������ڼ�¼Լ 552410.0015 ���ڣ��������Զ�Ӧ result.json Ϊ׼��

CPU �̼����¹���������δ������ɣ����̼��� RTL �ı䣬��������ȷ�ϱ�������֤������ֱ�����þ� simv �Ľ��ۡ����ֶ��� HDL ���Կ���������ʷĿ¼�����ܽ�ƾ�������ļ���ɾ�� dc/runs��

�� real12_verify_01 �ѹ鵵����ʷ�ű��ľ�·���Ѳ�����Ч����ǰ�����ʽʹ���µĹ�������·����
