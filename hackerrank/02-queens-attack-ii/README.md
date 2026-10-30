# 02 - Queen's Attack II

**Plataforma:** HackerRank · **Linguagem:** C++ · **Dificuldade:** Medium

## Arquivos
| Arquivo | Conteúdo |
|---------|----------|
| `template.cpp` | Código **original** entregue pelo HackerRank (função `queensAttack` vazia) |
| `solution.cpp` | Código **resolvido** (é este que se cola no site) |
| `tests/` | Casos de teste (`N.in` entrada, `N.out` saída esperada) |

## Enunciado
Tabuleiro `n x n` com uma rainha em `(r_q, c_q)` e `k` obstáculos. Contar quantas casas a rainha
ataca nas 8 direções (horizontal, vertical e diagonais). Um obstáculo bloqueia a casa dele e tudo
que vem depois naquela direção. Limites do HackerRank: n até 10^5 e k até 10^5.

## Como foi resolvido

### 1. Descartar a força bruta
Montar uma matriz `n x n` precisaria de até 10^10 casas, o que estoura memória e tempo.
Como só importam as 8 direções a partir da rainha, não precisamos do tabuleiro inteiro.

### 2. Alcance sem obstáculos
Para cada direção `(dr, dc)` contamos quantas casas existem até a borda. O limite é a
borda mais próxima entre linha e coluna:

- `dr > 0`: `n - r_q` · `dr < 0`: `r_q - 1` · `dr == 0`: sem limite pela linha
- `dc > 0`: `n - c_q` · `dc < 0`: `c_q - 1` · `dc == 0`: sem limite pela coluna
- alcance = `min(limite da linha, limite da coluna)`

Exemplo: n=8, rainha em (4,4), direção `(+1,+1)` => `min(8-4, 8-4) = 4`.

### 3. Aplicar os obstáculos
Para cada obstáculo calculamos a diferença para a rainha: `diffR = r_o - r_q`, `diffC = c_o - c_q`.

- Está em linha reta se `diffR == 0`, `diffC == 0` ou `|diffR| == |diffC|`. Senão, é ignorado.
- A direção é `(sinal(diffR), sinal(diffC))` e a distância é `max(|diffR|, |diffC|)`.
- Ele bloqueia a própria casa e as seguintes, então o alcance vira `min(alcance, distância - 1)`.

Obstáculos repetidos ou atrás de outro obstáculo não atrapalham, pois o `min` mantém o mais próximo.

### 4. Somar
A resposta é a soma dos 8 alcances.

### Mudança entre template e solução
Apenas o corpo de `queensAttack` foi preenchido (compare `template.cpp` com `solution.cpp`).
O `main` e os helpers (`ltrim`, `rtrim`, `split`) ficaram intactos.

- **Complexidade:** tempo O(k), espaço O(1) extra.
- `int` basta: o total é no máximo 8 * 10^5.

## Como foi testado
O `main` do HackerRank escreve em `getenv("OUTPUT_PATH")`, que não existe localmente. Por isso o
`run_tests.ps1` define essa variável, executa cada `tests/N.in` e compara com `tests/N.out`.

```powershell
.\run_tests.ps1 hackerrank\02-queens-attack-ii
```

| # | Caso | Esperado | Motivo |
|---|------|----------|--------|
| 1 | n=4, sem obstáculos, rainha (4,4) | 9 | Sample 0 |
| 2 | n=5, 3 obstáculos, rainha (4,3) | 10 | Sample 1 |
| 3 | n=1 | 0 | Sample 2 (tabuleiro de 1 casa) |
| 4 | n=8, rainha (4,4), obstáculo (3,5) | 24 | exemplo da figura do enunciado |
| 5 | n=8, rainha (4,4), sem obstáculos | 27 | caso base do enunciado |
| 6 | n=3, rainha no centro cercada | 0 | obstáculos adjacentes em todas as direções |

**Resultado:** 6/6 passaram.
