#include "stdinc.h"
#include "byte_pattern.h"

namespace Font
{
	/*-----------------------------------------------*/

	errno_t heapAllocInitFlag_hook(CK2Version version) {
		std::string desc = "heap alloc init flag";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("59 85 C0 74 15 56 6A 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x7), 0x08, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t buffSizeLauncher_hook(CK2Version version) {
		std::string desc = "launcher font heap size change";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("68 90 26 00 00");
			if (byte_pattern::temp_instance().has_size(3, desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(0).address(3), 0x04, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(1).address(3), 0x04, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(2).address(3), 0x04, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t buffSizeMain_hook(CK2Version version) {
		std::string desc = "main font heap size change";

		switch (version) {
		case v2_8_X:
			byte_pattern::temp_instance().find_pattern("68 84 26 00 00");
			if (byte_pattern::temp_instance().has_size(3,desc)) {
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(0).address(3), 0x04, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(1).address(3), 0x04, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get(2).address(3), 0x04, true);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(CK2Version version) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("map font view");

		// �t�H���g�̃o�b�t�@�g���i�{�́j
		result |= buffSizeMain_hook(version);
		// �t�H���g�̃o�b�t�@�g���i�����`���[�j
		result |= buffSizeLauncher_hook(version);
		// �q�[�v�N���A�t���O
		result |= heapAllocInitFlag_hook(version);

		return result;
	}
}