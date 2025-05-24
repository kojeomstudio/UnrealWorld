#!/bin/bash

# 현재 스크립트가 위치한 디렉토리를 기준으로 경로 설정
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
GENERATOR_FILE_PATH="$SCRIPT_DIR/../../GenerateProjectFiles.command"

# UnrealWorld.uproject 경로 설정
UPROJECT_PATH="$SCRIPT_DIR/UnrealWorld.uproject"

# GenerateProjectFiles.command 스크립트 호출
"$GENERATOR_FILE_PATH" "$UPROJECT_PATH" -Game -Engine