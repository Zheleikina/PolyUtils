# PolyUtils: контракт бібліотеки, версія API 1.0

**Платформа:** Windows x64, MSVC, Release.
**Файли:** `bin/PolyUtils.dll`, `lib/PolyUtils.lib` (import library), `include/PolyUtils.h`.
**Експорт:** усі функції `extern "C"`, конвенція виклику cdecl (за замовчуванням для x64), імена без декорування.
**Зв'язування:** неявне (`.h` + `.lib`) та явне (`LoadLibrary` + `GetProcAddress`).

## Подання полінома

Поліном це масив `double`: `coeffs[i]` є коефіцієнтом при `x^i`.
`n` це кількість коефіцієнтів (степінь = `n - 1`).
Приклад: `1 + 2x + 3x²` → `{1, 2, 3}`, `n = 3`.

## Загальні правила

- Бібліотека **нічого не виділяє і не звільняє**. Результат записується у буфер, наданий викликачем.
- Допустимий розмір вхідного полінома: `1 <= n <= 10000`.
- Буфер результату не повинен перетинатися з вхідними масивами.
- Вхідні масиви не змінюються.
- Функції не кидають винятків і не завершують процес при некоректних параметрах.
- Потокобезпечність: функції не мають глобального стану, тож їх можна викликати з різних потоків.
- Повернене значення `>= 0` це успіх (зазвичай кількість записаних коефіцієнтів), `< 0` це код помилки.

## Коди помилок

| Код | Константа | Значення |
|-----|-----------|----------|
| -1 | `POLY_ERR_NULL` | nullptr в обов'язковому параметрі |
| -2 | `POLY_ERR_SIZE` | розмір `n <= 0` або `n > 10000` |
| -3 | `POLY_ERR_BUFFER` | `outCapacity` менша за потрібну |

Порядок перевірок: спочатку nullptr, потім розміри, потім ємність буфера.
При помилці вміст вихідного буфера не визначений (його не слід використовувати).

## Функції

### PolyAdd
```c
int PolyAdd(const double* a, int na, const double* b, int nb, double* out, int outCapacity);
```
Сума поліномів. Потрібна ємність: `max(na, nb)`.
Повертає `max(na, nb)`. Старші відсутні коефіцієнти вважаються нулями.

### PolyMultiply
```c
int PolyMultiply(const double* a, int na, const double* b, int nb, double* out, int outCapacity);
```
Добуток поліномів (згортка коефіцієнтів). Потрібна ємність: `na + nb - 1`.
Повертає `na + nb - 1`.

### PolyEvaluate
```c
int PolyEvaluate(const double* coeffs, int n, double x, double* result);
```
Значення полінома в точці `x` (схема Горнера). Результат записується в `*result`.
Повертає `0` при успіху. NaN/Inf у `x` або коефіцієнтах дають NaN/Inf у результаті і помилкою не вважаються.

### PolyDerivative
```c
int PolyDerivative(const double* coeffs, int n, double* out, int outCapacity);
```
Похідна. Потрібна ємність: `max(n - 1, 1)`.
Повертає `n - 1` для `n >= 2`. Для `n == 1` (константа) повертає `1`, `out[0] = 0`.

### PolyIntegral
```c
int PolyIntegral(const double* coeffs, int n, double constant, double* out, int outCapacity);
```
Первісна: `out[0] = constant`, `out[i+1] = coeffs[i] / (i+1)`. Потрібна ємність: `n + 1`.
Повертає `n + 1`.

## Граничні випадки

| Ситуація | Результат |
|----------|-----------|
| nullptr у будь-якому обов'язковому вказівнику | `-1` |
| `n == 0`, `n < 0` або `n > 10000` | `-2` |
| `outCapacity` менша за потрібну | `-3` |
| Похідна константи | `1`, `out[0] = 0` |
| NaN/Inf у даних | NaN/Inf у результаті, без помилки |

## Приклад (неявне зв'язування)

```cpp
#include "PolyUtils.h"
double p[] = {1, 2, 3}, r[8];
int n = PolyDerivative(p, 3, r, 8);   // n = 2, r = {2, 6}
```

## Приклад (явне зв'язування)

```cpp
typedef int (*PolyEvaluateFn)(const double*, int, double, double*);
HMODULE h = LoadLibraryA("PolyUtils.dll");
auto ev = (PolyEvaluateFn)GetProcAddress(h, "PolyEvaluate");
double p[] = {1, 2, 3}, v;
ev(p, 3, 2.0, &v);                    // v = 17
FreeLibrary(h);
```

## Версія
API 1.0, PolyUtils.dll.