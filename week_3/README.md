<h1><strong >힙 생성 구현하기</strong></h1>
<hr>

## 문제 1 (삽입식 힙 생성)

### 1. 구현 조건
- 키들은 한 개씩 차례로 삽입 명령과 함께 주어진다. 즉, 키가 입력될 때마다 즉시 힙에 삽입해야 한다. 만약 이렇게 하지 않고 문제 2에서 하는 것처럼 키들이 모두 입력되기를 기다려 한꺼번에 상향식으로 힙을 생성하면 대화식 프로그램의 인쇄(p) 또는 삭제(d) 명령의 수행이 어려워진다.
- 대화식 프로그램에 주어지는 명령은 i, d, p, q 네 가지며 각 명령에 대해 다음과 같이 수행해야 한다.
    - `i` <키> : <키>를 힙에 삽입하고 0을 인쇄.
    - `d` : 힙에서 삭제(이때 루트에 저장된 키가 삭제되어야 한다)하여 반환된 키를 인쇄.
    - `p` : 힙의 내용을 인쇄(이때 이진트리의 레벨순서로 항목들을 인쇄해야 한다)하고 프로그램 종료
      ‘레벨순서‘란 이진트리의 레벨 0의 노드부터 다음 레벨 1, 2, 3, ...의 노드들을 차례로 방문한다. 같은 레벨의 노드들은 왼쪽에서 오른쪽으로 방문한다.
    - `q` : 프로그램 종료
- 힙 인쇄 명령 p는 힙의 크기가 1 이상인 경우에만 적용한다고 전제한다.

### 2. 입출력 형식
- main 함수는 아래 형식의 표준입력으로 대화식 명령들을 입력받는다.
    - 첫 번째 ~ 마지막-1 라인 : 명령 i, d, p 가운데 하나
    - 마지막 라인 : 명령 q
- main 함수는 아래 형식의 표준출력으로 각 명령에 응답한다.
    - 0 (i 명령인 경우)
    - 키 (d 명령인 경우)
    - 힙 내용 (p 명령인 경우)

### 3. 예시

|입력 예시| 출력 예시|
|---|---|
|i 209 ↦ 키 209 삽입|0 ↦ 삽입 완료|
|i 400 ↦ 키 400 삽입| |
|d ↦ 삭제|400 ↦ 삭제 키 반환|
|i 77 ↦ 키 77 삽입|0 ↦ 삽입 완료|
|d ↦ 삭제|209 ↦ 삭제 키 반환|
|p ↦ 인쇄|□77 ↦ 힙 인쇄|
|q ↦ 종료||

---

## 문제 2 (상향식 힙 생성)

### 1. 구현 조건
- 이번엔 키들이 미리 한꺼번에 주어진다. 이들을 차례로 초기 배열에 저장한다.
- 초기 배열에 저장된 키들을 상향식으로 재배치하여 힙을 생성한다. 상향식 힙 생성을 위한 재귀 또는 비재귀 방식의 알고리즘 가운데 어느 전략을 사용해도 좋다.
- 참고로 재귀, 비재귀 두 가지 방식 모두 O(n) 시간에 수행 가능하다. 그렇게 되도록 작성해야 한다.

### 2. 입출력 형식
- main 함수는 아래 형식의 표준입력으로 키들을 한꺼번에 입력받는다.
    - 첫 번째 라인 : 키 개수
    - 두 번째 라인 : 키들
- main 함수는 아래 형식의 표준출력으로 생성된 힙을 인쇄한다.
    - 첫 번째 라인 : 힙 내용 (레벨 순서)

### 3. 예시

|입력 예시| 출력 예시|
|---|---|
|3 ↦ 키 개수|□400 209 77 ↦ 힙 인쇄|
|209 400 77 ↦ 키들| |