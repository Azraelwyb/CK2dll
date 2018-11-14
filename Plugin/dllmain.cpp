#include "stdinc.h"
#include "byte_pattern.h"

BOOL WINAPI DllMain(HMODULE module, DWORD reason, void *reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        byte_pattern::start_log(L"ck2jps");

		// version�𕶎��񂩂�擾
		CK2Version version = Misc::getVersion();

		errno_t success = NOERROR;

		// �}�b�v�t�H���g�\������
		success |= MapView::init(version);

		// �}�b�v�t�H���gjustify
		success |= MapJustify::init(version);

		// �}�b�v�t�H���g���������P
		success |= MapAdj::init(version);

		// �}�b�v�t�H���g�\�������Q
		success |= MapAdj2::init(version);

		// �}�b�v�t�H���g�\�������R
		success |= MapAdj3::init(version);

		// �t�H���g���[�f�B���O����
		success |= Font::init(version);

		// �I�����̃_�C�A���O�̉ԕ���
		//success |= DecorativeLetterEndDialog::init(version);

		// �_�C�A���O�̉ԕ���
		//success |= DecorativeLetterDialog::init(version);

		// �p���_�C�A���O�̉ԕ���
		//success |= DecorativeLetterInheritDialog::init(version);

		// Button�ƃc�[���`�b�v
		success |= ButtonAndTooltip::init(version);

		// ���C���e�L�X�g
		success |= MainText::init(version);

		// ���C���e�L�X�g���s�����i�_�C�A���O�j
		success |= MainTextLineBreak::init(version);

		// �j�b�N�l�[���C��
		//success |= NickNameFix::init(version);

		// Dynasty��-id�����Ȃ��悤�ɂ���
		success |= NoDynastyId::init(version);

		// IME
		success |= IME::init(version);

		//Input
		success |= Input::init(version);

		//Unknown 3
		success |= Unk3::init(version);

		//Unknown 4
		success |= Unk4::init(version);

		// issue33
		//success |= Issue33::init(version);

		// issue32
		//success |= Issue32::init(version);

		// ���t�\�L�̕ύX
		success |= DateFormat::init(version);

		if (success == NOERROR) {
			byte_pattern::debug_output2("Multibyte DLL [OK]");
		}
		else {
			MessageBoxW(NULL, L"[Multibyte DLL ERROR]\nThis game version is not supported by Multibyte DLL.\nPlease delete d3d9.dll and restart game.\nOr check new version dll.\n\nhttps://github.com/matanki-saito/CK2Dll", L"Multibyte DLL", MB_OK);
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
