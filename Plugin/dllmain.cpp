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

		// �}�b�v�t�H���g�\��
		MapView::init(version);

		// �}�b�v�t�H���gjustify
		MapJustify::init(version);

		// �t�H���g
		Font::init(version);

		// �I�����̃_�C�A���O�̉ԕ���
		DecorativeLetterEndDialog::init(version);

		// �_�C�A���O�̉ԕ���
		DecorativeLetterDialog::init(version);

		// �p���_�C�A���O�̉ԕ���
		DecorativeLetterInheritDialog::init(version);

		// Button�ƃc�[���`�b�v
		ButtonAndTooltip::init(version);

		// ���C���e�L�X�g
		MainText::init(version);

		if (success == NOERROR) {
			//MessageBoxW(NULL, L"[OK]", L"Multibyte DLL", MB_OK);
			byte_pattern::temp_instance().debug_output2("DLL [OK]");
		}
		else {
			MessageBoxW(NULL, L"[NG]", L"Multibyte DLL", MB_OK);
			byte_pattern::temp_instance().debug_output2("DLL [NG]");
			exit(-1);
		}

    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        byte_pattern::shutdown_log();
    }

    return TRUE;
}
