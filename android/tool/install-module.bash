#!/bin/bash
set -ueo pipefail
script_dir=$(cd $(dirname "$0");pwd)

ick_repo_module_path="android/IronCake/IronCake"
ick_module_links=(
	"build.gradle"
	"proguard-rules.txt"
	"src"
	)

is_studio_root(){
	local path="$1"
	if [[ -d "$path/.idea" && -f "$path/settings.gradle" ]] ; then 
		echo "1"
	else
		echo "0"
	fi
}

is_ick_root(){
	local path="$1"
	if [[ -f "$path/$ick_repo_module_path/build.gradle" ]] ; then
		echo "1" 
	else 
		echo "0" 
	fi
}

main(){
	echo "このスクリプトは廃止されました。"
	return 1

	if [[ "$(is_studio_root ".")" == 0 ]] ; then
		echo "[$(pwd)]はAndroid Studioのプロジェクトディレクトリではありません。"
		echo "インストール先のAndroid Studioのプロジェクトディレクトリで実行してください。"
		return 1
	fi

	echo "[$(pwd)]にIronCakeのモジュールをインストールします。"
	echo -n "ここからIronCakeのリポジトリルートへの相対パスを入力してください。"
	read -e  -p ": " ick_root_path
	
	if [[ "$(is_ick_root "./$ick_root_path")" == 0 ]] ; then
		echo "[$(pwd)/$ick_root_path]はIronCakeのリポジトリルートではありません。"
		return 1
	fi

	local module_name="$(basename "$ick_repo_module_path")"
	
	mkdir -pv "$module_name"
	cd "$module_name"

	for link_name in "${ick_module_links[@]:0}"	; do
		ln -fhsv "../$ick_root_path/$ick_repo_module_path/$link_name" "."
	done

	echo "モジュールの配置が完了しました。"
	echo "settings.gradleに下記を追記してください。"
	echo ""
	echo "include ':$module_name'"
	echo ""
	echo "アプリケーションモジュールのbuild.gradleにて、"
	echo "dependenciesに下記を追記してください。"
	echo ""
	echo "compile project(':$module_name')"
	echo ""
	return 0
}

main "$@"
exit $?