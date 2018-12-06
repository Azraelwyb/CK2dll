#include "stdinc.h"
#include "byte_pattern.h"

namespace MapAdj2
{
	/*-----------------------------------------------*/

	uintptr_t l_5_end_v28;
	__declspec(naked) void l_1_start_v28()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz l_10;
	
			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz l_11;
	
			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz l_12;
	
			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz l_13;
	
			jmp l_2;
	
		l_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp l_1x;
		l_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp l_1x;
		l_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp l_1x;
		l_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;
			jmp l_1x;
	
		l_1x:
			add esi, 2;
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja l_3
			mov eax, NOT_DEF;
		l_3:
			jmp l_4;
	
		l_2:
			movzx eax, byte ptr[eax + esi];
		l_4:
			mov edx, [ebp - 0x0C];
			push l_5_end_v28;
			ret;
		}
	}
	
	uintptr_t l_5_end_v301;
	__declspec(naked) void l_1_start_v301()
	{
		__asm {
			cmp byte ptr[eax + esi], ESCAPE_SEQ_1;
			jz l_10;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_2;
			jz l_11;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_3;
			jz l_12;

			cmp byte ptr[eax + esi], ESCAPE_SEQ_4;
			jz l_13;

			jmp l_2;

		l_10:
			movzx eax, word ptr[eax + esi + 1];
			jmp l_1x;
		l_11:
			movzx eax, word ptr[eax + esi + 1];
			sub eax, SHIFT_2;
			jmp l_1x;
		l_12:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_3;
			jmp l_1x;
		l_13:
			movzx eax, word ptr[eax + esi + 1];
			add eax, SHIFT_4;
			jmp l_1x;

		l_1x:
			add esi, 2;
			movzx eax, ax;
			cmp eax, NO_FONT;
			ja l_3
			mov eax, NOT_DEF;
		l_3:
			jmp l_4;

		l_2:
			movzx eax, byte ptr[eax + esi];
		l_4:
			mov ebx, [ebp - 0x10]; // �ύX
			push l_5_end_v301;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t fix1_hook(RunOptions *options) {
		std::string desc = "fix";

		switch (options->version) {
		case v2_8_X:
		case v3_0_0:
			// mov edx,[ebp+var_C]
			byte_pattern::temp_instance().find_pattern("8B 55 F4 0F B6 04 30");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), l_1_start_v28);
				// mov eax,[edx+eax*4+OFFSET]
				l_5_end_v28 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;

		case v3_0_X: // ���̏ꏊ�ŗǂ��̂����M���Ȃ�
			// mov ebx,[ebp+var_10]
			byte_pattern::temp_instance().find_pattern("8B 5D F0 0F B6 04 30 8B 84 83 A4 00 00 00");
			if (byte_pattern::temp_instance().has_size(1, desc)) {
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), l_1_start_v301);
				// mov eax, [ebx+eax*4+OFFSET]
				l_5_end_v301 = byte_pattern::temp_instance().get_first().address(7);
			}
			else return CK2ERROR1;
			return NOERROR;
		}
		return CK2ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(RunOptions *options) {
		errno_t result = NOERROR;

		byte_pattern::debug_output2("map adj 2");

		// �}�b�v�\���̒����@���̂Q
		result |= fix1_hook(options);

		return result;
	}
}