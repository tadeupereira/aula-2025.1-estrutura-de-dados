### 6.5.3. Sistema de Cursos Online com Trilhas de Aprendizagem
#### 6.5.3.1. Objetivo
Criar um sistema para gerenciar cursos online e organizar alunos interessados em se inscrever.

#### 6.5.3.2. Estruturas do domínio
    • Lista de cursos disponíveis (estrutura 1)
    • Fila de espera de alunos por curso (estrutura 2)

#### 6.5.3.3. Descrição
Cada curso terá título, área (ex: Programação, Design, etc.) e número máximo de vagas. Quando um curso atinge seu limite, novos alunos são colocados em uma fila de espera. Cada aluno é identificado por nome e e-mail. O sistema deve permitir o gerenciamento dos cursos e dos alunos em fila.

#### 6.5.3.4. MVP (Entrega única)
✅ Implementar estrutura de lista dinâmica para os cursos.

✅ Implementar estrutura de fila dinâmica para fila de espera de alunos por curso.

✅ Funções para:

    • Cadastrar novo curso.
    • Remover curso.
    • Listar todos os cursos.
    • Inscrever aluno no curso (entra na fila se não houver vagas).
    • Liberar vaga no curso (aluno da fila é chamado).
    • Buscar curso por título.
    • Ordenar cursos por título ou área.

---
