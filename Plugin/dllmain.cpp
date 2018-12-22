#include "stdinc.h"
#include "byte_pattern.h"

BOOL WINAPI DllMain(HMODULE module, DWORD reason, void *reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        byte_pattern::start_log(L"ck2jps");

		// �I�v�V������ini�t�@�C������擾
		RunOptions options = RunOptions();
		Misc::getOptionsByINI(&options);

		// version�𕶎��񂩂�擾
		CK2Version version = Misc::getVersion();

		// version�ݒ�
		options.version = version;

		errno_t success = NOERROR;

		// �}�b�v�t�H���g�\������
		success |= MapView::init(&options);

		// �}�b�v�t�H���gjustify
		success |= MapJustify::init(&options);

		// �}�b�v�t�H���g���������P
		success |= MapAdj::init(&options);

		// �}�b�v�t�H���g�\�������Q
		success |= MapAdj2::init(&options);

		// �}�b�v�t�H���g�\�������R �����炭�����啶���̉���
		success |= MapAdj3::init(&options);

		// �t�H���g���[�f�B���O����
		success |= Font::init(&options);

		// �I�����̃_�C�A���O�̉ԕ���
		success |= DecorativeLetterEndDialog::init(&options);

		// �_�C�A���O�̉ԕ���
		success |= DecorativeLetterDialog::init(&options);

		// �p���_�C�A���O�̉ԕ���
		success |= DecorativeLetterInheritDialog::init(&options);

		// Button�ƃc�[���`�b�v
		success |= ButtonAndTooltip::init(&options);

		// ���C���e�L�X�g
		success |= MainText::init(&options);

		// ���C���e�L�X�g���s�����i�_�C�A���O�j
		success |= MainTextLineBreak::init(&options);

		// �j�b�N�l�[���C��
		success |= NickNameFix::init(&options);

		// Dynasty��-id�����Ȃ��悤�ɂ���
		success |= NoDynastyId::init(&options);

		// IME
		success |= IME::init(&options);

		//Input
		success |= Input::init(&options);

		//Unknown 3
		success |= Unk3::init(&options);
		
		//Unknown 4 : OK
		success |= Unk4::init(&options);

		// issue33 �uXXX�ɒ����𐾂��Ă���v�ɂ�����
		// https://github.com/matanki-saito/CK2dll/issues/33
		success |= Issue33::init(&options);

		// issue32 �� ���O�ɂȂ��Ă���̂ŁA���{��̂Ƃ��̂ݖ��O �Ƃɂ�����
		// https://github.com/matanki-saito/CK2dll/issues/32
		success |= Issue32::init(&options);

		// ���t�\�L�̕ύX
		success |= DateFormat::init(&options);

		// �t�@�C���ۑ�
		success |= FileSave::init(&options);

		if (success == NOERROR) {
			byte_pattern::debug_output2("Multibyte DLL [OK]");
		}
		else {
			MessageBoxW(NULL, L"[Multibyte DLL ERROR]\n\nYour current version is 3.0.1.1 is not supported by now.\n\nThe latest supprot version is 3.0.1, please rollback your main exe.\n\Or play game in english after delete d3d9.dll...\n\n Thanks", L"Multibyte DLL", MB_OK);
			byte_pattern::debug_output2("Multibyte DLL [NG]");
			exit(-1);
		}

    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        byte_pattern::shutdown_log();
    }

    return TRUE;
}
