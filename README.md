# Dining-Philosophers-Problem

운영체제의 교착 상태(DeadLock)를 설명하기 위한 '식사하는 철학자' 문제를 해결하는 코드입니다.

## 목차

1. [데드락이란?](#1️⃣-데드락이란)
2. [식사하는 철학자 문제](#2️⃣-식사하는-철학자-문제)
3. [문제해결](#3️⃣-문제-해결)

## 1️⃣ 데드락이란?

교착 상태(DeadLock)란 두 개 이상의 프로세스나 스레드가 서로 점유하고 있는 자원을 기다리며 영원히 대기하는 상황을 말한다.

### 데드락의 발생 조건

데드락은 다음 4가지 조건을 모두 만족했을 때 발생한다.

- 상호 배제 (Mutual exclusion)
  - 하나의 자원은 한 번에 한 프로세스만 사용할 수 있다.
- 점유 대기 (Hold and wait)
  - 최소 하나의 자원을 가진 프로세스가 다른 자원을 기다릴 때, 보유하고 있는 자원을 놓지 않고 가지면서 기다린다.
- 비선점 (No preemption)
  - 한 프로세스에 할당된 자원은, 그 프로세스가 사용을 끝낼 때까지 OS에서 강제로 빼앗을 수 없다.
- 순환 대기 (Circular wait)
  - 자원을 기다리는 프로세스 간에는 사이클이 형성되어야 한다.

### 데드락 해결 방법

- 예방(Prevention)

  - 위의 데드락 발생 조건 중 1가지를 차단하므로써 해결한다.
  - 자원의 낭비가 심하다는 단점이 있다.

- 회피(Avoidance)

  - 데드락이 발생하기 전 데드락을 예측하고 회피하는 방법이다.
  - 회피 알고리즘을 이용해 미리 자원들의 최대 가능 할당량을 시뮬레이션하여 데드락의 가능성을 탐지한다.
  - 자원을 요청할 때마다 알고리즘을 사용하기 때문에 오버헤드가 크다.

- 탐지(Detection) 및 회복(Recovery)
  - 교착 상태를 허용하며, 탐지 알고리즘을 통해 교착상태를 탐지하면 복구하는 방법이다.
  - 교착 상태를 완전히 예방하는 데에는 비용과 자원의 낭비가 심하기 때문에, 적절한 탐지 알고리즘의 호출을 통해 교착 상태 문제를 해결할 수도 있다.

## 2️⃣ 식사하는 철학자 문제

[운영체제 - 식사하는 철학자](https://namu.wiki/w/%EC%8B%9D%EC%82%AC%ED%95%98%EB%8A%94%20%EC%B2%A0%ED%95%99%EC%9E%90%20%EB%AC%B8%EC%A0%9C)

위의 식사하는 철학자 문제를 응용하여 몇 가지 규칙이 포함된 문제를 해결하려고 한다.

### 문제 규칙

- 프로세스는 1개이며, 멀티 스레드 방식을 사용하여 문제를 해결한다.
- 실행파일은 인자로 `{number_of_philosopher} {time_to_die} {time_to_eat} time_to_sleep}`을 받아온다.
- 다음 인자는 옵션으로 받아올 수 있으며, `{must_eat_cnt}`를 받아온다.
- 철학자는 `eat`, `sleep`, `think`를 순서대로 수행하고, 각각의 행동을 할 때마다 그 때의 시각과 자신의 id를 출력한다.
- 철학자는 eat을 수행 한 뒤 `time to die`시간이 지나도록 음식을 먹지 못하면 굶어 죽는다.
- 철학자가 1명이라도 죽으면 죽었다는 출력 메세지와 함께 프로그램은 종료된다.
- 인자로 `{must_eat_cnt}`를 받은 경우, 모든 철학자가 `must_eat_cnt` 횟수만큼 식사를 완료하면 _(배부른 상태에 도달하면)_ 프로그램이 종료된다.
- 이 때 출력 시간은 `<time.h>` 헤더에 포함되어있는 `clock_gettime` 함수를 사용한다. _(리눅스계열 OS의 시스템콜 함수)_

## 3️⃣ 문제 해결

### 스레드 간의 동기화

- 각 스레드간의 동기화 방법으로 `mutex`를 사용하였다.
- 뮤텍스 배열 fork를 만들어 fork[id] mutex에 접근하면 해당 id의 포크(젓가락)을 집은 것으로 생각하였다.
- 또한 프로그램이 종료하는 조건을 감시하기 위해 메인 스레드에서 `monitor()` 함수를 실행시켜 죽는 경우를 검사하였다.
- 철학자가 죽거나, 모두 배부른 상태에 도달한 경우 `monitor()` 함수에서 mutex에 접근하여 프로그램 종료 플래그를 올려준다.

### 최적화와 관련된 고민

- 위의 방법은 모든 스레드에서 반복적으로 mutex에 접근하기 때문에 잦은 context switching이 발생한다. 이에 비해 임계구역에서는 특별한 동작을 수행하지 않기 때문에, Context Switching이 적게 발생하는 SpinLock 방식과 Mutex를 사용한 방식을 고민하였다.
