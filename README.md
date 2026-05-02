# Peechi Language 🐣

**Peechi** is a Brazilian open-source programming language created to start simple and grow with power.

**Peechi** é uma linguagem de programação brasileira e open-source, criada para começar simples e crescer com poder.

---

## Português

### Sobre

Peechi é uma linguagem de programação criada por **Maharich Campos**.

A ideia nasceu em 2023 com uma pergunta simples: **“e se eu criasse minha própria linguagem de programação?”**. Desde então, deixou de ser apenas uma curiosidade e se tornou um projeto real.

A Peechi começa simples, em um nível alto e acessível, mas foi pensada para crescer com o tempo, chegando a recursos mais avançados e mais próximos do baixo nível. A ideia é criar uma linguagem que não limite a pessoa, mas acompanhe sua evolução.

O nome **Peechi** vem de **“chick”** (pintinho) e do som que ele faz. O símbolo do pintinho saindo do ovo representa um começo pequeno, a quebra de barreiras e o crescimento com o tempo.

A extensão oficial **`.pee`** também carrega esse significado: cada arquivo é como uma voz, uma expressão. “Pee” é o som do pintinho — e, ao programar, você escreve suas próprias palavras e sua própria história.

**Simples no começo, poderosa no final.**

### Informações

- **Extensão oficial:** `.pee`
- **Comando planejado:** `peechi`
- **Criador:** Maharich Campos
- **Versão atual:** `0.1.1`
- **Sistema suportado por enquanto:** Windows
- **Licença:** MIT
- **Status:** em desenvolvimento
- **Filosofia:** simples no começo, poderosa no final

### Recursos da versão 0.1.1

A versão `0.1.1` mantém o núcleo inicial da Peechi e corrige o comportamento da concatenação com `+`.

Ela inclui:

- `print(...)`
- strings com aspas duplas e simples
- números
- booleanos
- variáveis por atribuição direta
- operadores aritméticos básicos
- operadores de comparação
- `if`
- `else`
- `while`
- `loop`
- `break`
- comentários com `//`
- concatenação de texto com `+`
- múltiplos argumentos em `print(...)`

### Correção da versão 0.1.1

A regra do operador `+` foi ajustada para respeitar melhor os tipos:

- `número + número` faz soma
- `texto + texto` faz concatenação
- `texto + número` gera erro
- `número + texto` gera erro

Exemplo válido:

```pee
print("Olá, " + "mundo!")
```

Exemplo inválido:

```pee
print("Idade: " + 15)
```

Essa correção evita conversões automáticas inesperadas e deixa o comportamento da linguagem mais claro.

### Instalação no Windows

Baixe o instalador da Peechi e execute o arquivo:

```text
Peechi-Setup.exe
```

O instalador coloca a Peechi em:

```text
C:\Program Files\Peechi
```

E adiciona a pasta da Peechi ao **PATH** do Windows.

Depois da instalação, feche e abra novamente o terminal e teste:

```cmd
peechi
```

ou:

```cmd
peechi.exe
```

### Aviso

A Peechi ainda está em desenvolvimento. A versão `0.1.1` pode conter erros, mudanças incompletas e comportamentos inesperados.

### Aviso sobre o nome

O nome **“Peechi”** é reservado. Forks e projetos derivados devem usar outro nome.

A licença MIT permite usar, copiar, modificar e distribuir o código, mas este aviso deixa claro que o nome do projeto original deve ser preservado para o projeto oficial.

---

## English

### About

Peechi is a programming language created by **Maharich Campos**.

The idea was born in 2023 from a simple question: **“what if I created my own programming language?”**. Since then, it has grown from curiosity into a real project.

Peechi starts simple, at a high and accessible level, but it is designed to grow over time, reaching more advanced features and concepts closer to low-level programming. The goal is to create a language that does not limit people, but grows with them.

The name **Peechi** comes from **“chick”** and the sound it makes. The symbol of a chick hatching from an egg represents starting small, breaking barriers, and growing over time.

The official file extension **`.pee`** also carries this meaning: each file is like a voice, an expression. “Pee” is the sound a chick makes — and when you code, you write your own words and your own story.

**Simple at the beginning, powerful at the end.**

### Information

- **Official extension:** `.pee`
- **Planned command:** `peechi`
- **Creator:** Maharich Campos
- **Current version:** `0.1.1`
- **Supported system for now:** Windows
- **License:** MIT
- **Status:** under development
- **Philosophy:** simple at the beginning, powerful at the end

### Features in version 0.1.1

Version `0.1.1` keeps Peechi’s initial core and fixes the behavior of concatenation with `+`.

It includes:

- `print(...)`
- strings with double and single quotes
- numbers
- booleans
- variables through direct assignment
- basic arithmetic operators
- comparison operators
- `if`
- `else`
- `while`
- `loop`
- `break`
- comments with `//`
- text concatenation with `+`
- multiple arguments in `print(...)`

### Fix in version 0.1.1

The rule for the `+` operator was adjusted to better respect types:

- `number + number` performs addition
- `text + text` performs concatenation
- `text + number` raises an error
- `number + text` raises an error

Valid example:

```pee
print("Hello, " + "world!")
```

Invalid example:

```pee
print("Age: " + 15)
```

This fix avoids unexpected automatic conversions and makes the language behavior clearer.

### Windows installation

Download the Peechi installer and run:

```text
Peechi-Setup.exe
```

The installer places Peechi in:

```text
C:\Program Files\Peechi
```

And adds the Peechi folder to the Windows **PATH**.

After installation, close and reopen your terminal and test:

```cmd
peechi
```

or:

```cmd
peechi.exe
```

### Notice

Peechi is still under development. Version `0.1.1` may contain bugs, incomplete changes, and unexpected behavior.

### Name notice

The name **“Peechi”** is reserved. Forks and derivative projects must use a different name.

The MIT License allows people to use, copy, modify, and distribute the code, but this notice makes it clear that the original project name should remain reserved for the official project.

---

## Links

- Website: [Peechi Language](https://maharich.page.gd/)
- Discord: [Peechi Language Official](https://discord.gg/eyJEthFzPx)
- X/Twitter: Coming Soon / Em breve

---

## License

Peechi is open-source software licensed under the **MIT License**.

See the [`LICENSE`](LICENSE) file for details.
