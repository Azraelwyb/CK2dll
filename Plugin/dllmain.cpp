﻿#include "stdinc.h"
#include "byte_pattern.h"
#include "moddl.h"

BOOL WINAPI DllMain(HMODULE module, DWORD reason, void *reserved)
{
	
    if (reason == DLL_PROCESS_ATTACH)
    {
		// moddownload
		wchar_t myDocumentPath[MAX_PATH];
		SHGetSpecialFolderPath(NULL, myDocumentPath, CSIDL_PERSONAL, 0);

		const path gameDirPath = path{ myDocumentPath } / L"Paradox Interactive" / L"Crusader Kings II";
		if (!InitAutoUpdate(gameDirPath)) exit(-1);

        byte_pattern::start_log(L"ck2jps");

		// オプションをiniファイルから取得
		RunOptions options = RunOptions();
		Misc::getOptionsByINI(&options);

		// versionを文字列から取得
		CK2Version version = Misc::getVersion();

		// version設定
		options.version = version;

		errno_t success = NOERROR;

		// マップフォント表示処理
		success |= MapView::init(&options);

		// マップフォントjustify
		success |= MapJustify::init(&options);

		// マップフォント調整処理１
		success |= MapAdj::init(&options);

		// マップフォント表示調整２
		success |= MapAdj2::init(&options);

		// マップフォント表示調整３ おそらく強制大文字の解除
		success |= MapAdj3::init(&options);

		// フォントローディング処理
		success |= Font::init(&options);

		// 終了時のダイアログの花文字
		success |= DecorativeLetterEndDialog::init(&options);

		// ダイアログの花文字
		success |= DecorativeLetterDialog::init(&options);

		// 継承ダイアログの花文字
		success |= DecorativeLetterInheritDialog::init(&options);

		// Buttonとツールチップ
		success |= ButtonAndTooltip::init(&options);

		// メインテキスト
		success |= MainText::init(&options);

		// メインテキスト改行処理（ダイアログ）
		success |= MainTextLineBreak::init(&options);

		// ニックネーム修正
		success |= NickNameFix::init(&options);

		// Dynastyに-idがつかないようにする
		success |= NoDynastyId::init(&options);

		// IME
		success |= IME::init(&options);

		//Input
		success |= Input::init(&options);

		//Unknown 3
		success |= Unk3::init(&options);
		
		//Unknown 4 : OK
		success |= Unk4::init(&options);

		// issue33 「XXXに忠誠を誓っている」にしたい
		// https://github.com/matanki-saito/CK2dll/issues/33
		success |= Issue33::init(&options);

		// issue32 家 名前になっているので、日本語のときのみ名前 家にしたい
		// https://github.com/matanki-saito/CK2dll/issues/32
		success |= Issue32::init(&options);

		// 日付表記の変更
		success |= DateFormat::init(&options);

		// ファイル保存
		success |= FileSave::init(&options);

		if (success == NOERROR) {
			byte_pattern::debug_output2("Multibyte DLL [OK]");
		}
		else {
			MessageBoxW(NULL, L"[Multibyte DLL ERROR]\n\nThe latest supprot version is 3.0.1.1, please rollback your main exe.\n\Or play game in english after delete d3d9.dll...\n\n Thanks", L"Multibyte DLL", MB_OK);
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
