# 01 - Solve Me First

**Plataforma:** HackerRank · **Linguagem:** C++ · **Dificuldade:** Easy

## Arquivos
| Arquivo | Conteúdo |
|---------|----------|
| `template.cpp` | Código **original** entregue pelo HackerRank (função vazia) |
| `solution.cpp` | Código **resolvido** (é este que se cola no site) |
| `tests/` | Casos de teste (`N.in` entrada, `N.out` saída esperada) |

## Enunciado
Completar `solveMeFirst(a, b)` para retornar a soma de dois inteiros.

- Entrada: `a` e `b` (1 ≤ a, b ≤ 1000)
- Saída: `a + b`

| Entrada | Saída |
|---------|-------|
| `2 3`   | `5`   |

## Como foi resolvido
1. **Entender o template.** O `main` já lê dois números com `cin`, chama `solveMeFirst`
   e imprime o resultado com `cout`. Só falta o corpo da função.
2. **Pensar na solução.** O problema pede apenas a soma, então basta retornar `a + b`.
3. **Checar limites.** Com `a, b ≤ 1000` o maior resultado é 2000, que cabe em `int` sem overflow.
4. **Implementar.** Única mudança entre `template.cpp` e `solution.cpp`:

```cpp
// antes (template.cpp)
int solveMeFirst(int a, int b) {
 // Hint: Type return a+b; below:

}

// depois (solution.cpp)
int solveMeFirst(int a, int b) {
  return a + b;
}
```

- **Complexidade:** tempo O(1), espaço O(1).

## Como foi testado
Cada caso fica em `tests/N.in` / `tests/N.out`. O `run_tests.ps1` compila o `solution.cpp`,
executa cada entrada e compara a saída com o esperado.

```powershell
.\run_tests.ps1 hackerrank\01-solve-me-first
```

| # | Entrada     | Esperado | Motivo                |
|---|-------------|----------|-----------------------|
| 1 | `2 3`       | `5`      | sample do HackerRank  |
| 2 | `7 3`       | `10`     | exemplo do enunciado  |
| 3 | `1 1`       | `2`      | limite inferior       |
| 4 | `1000 1000` | `2000`   | limite superior       |

**Resultado:** 4/4 passaram.
