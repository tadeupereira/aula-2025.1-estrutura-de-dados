### 6.5.1. Sistema de Controle de Biblioteca Acadêmica
#### 6.5.1.1. Objetivo
Criar um sistema para gerenciar os livros e os empréstimos de uma biblioteca universitária.

#### 6.5.1.2. Estruturas do domínio
    • Lista de livros cadastrados (estrutura 1)
    • Fila de empréstimos por livro (estrutura 2)

#### 6.5.1.3. Descrição
Cada livro terá título, autor, código ISBN, e quantidade disponível. Para cada livro, pode haver uma fila de espera para empréstimo caso não haja unidades disponíveis. Os empréstimos respeitam a ordem de solicitação e deve ser informado o nome e CPF do usuário que está na fila de empréstimos.

#### 6.5.1.4. MVP (Entrega única)
✅ Implementar estrutura de lista dinâmica para os livro.

✅ Implementar estrutura de fila dinâmica para fila de espera por livro.

✅ Funções para:

    • Cadastrar livro.
    • Remover livro.
    • Listar todos os livros.
    • Solicitar empréstimo (entra na fila se não disponível).
    • Liberar empréstimo (remove da fila).
    • Buscar livro por título.
    • Ordenar livros por nome ou autor.

---
