## UnrealWorld
 언리얼 엔진5 기반 UnrealWorld 게임 프로젝트
___
**UE version**
1. UE5 5.5.2
2. 엔진 코드 별도 운용  (UE 라이센스 정책상 엔진 forked repo를 공개할 수 없음.)
___

> **메인 목표**  
> - LLM을 이용해 게임 내 에이전트를 제어하고, 실제 게임 서비스에 적용 가능한지 실험

> **서브 목표**  
> - 텍스처, 애니메이션 등 에셋 생성 자동화 및 관리  
> - 언리얼 엔진의 구조를 커스텀하여 LLM 통합에 최적화

## 🛠️ 기술 스택

- **엔진**: Unreal Engine 5.5.2 (https://github.com/kojeomstudio/UnrealEngine-Custom)
- **AI 프레임워크**: Ollama
- **프로그래밍 언어**: C++, C#, Python(if needed)
- **타겟 LLM**: Qwen3, Gemma3 에서 제공되는 0.5B ~ 14B 사이 모델

## 참고 논문
1. https://arxiv.org/pdf/2404.02039
2. https://arxiv.org/pdf/2411.05348
3. https://arxiv.org/pdf/2305.16291
4. https://arxiv.org/pdf/2310.08067