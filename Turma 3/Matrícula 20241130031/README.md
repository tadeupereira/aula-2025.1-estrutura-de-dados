### 6.5.2. Sistema de Planejamento de Viagens em Grupo
#### 6.5.2.1. Objetivo
Criar um sistema para organizar viagens e gerenciar os participantes interessados em cada viagem.

#### 6.5.2.2. Estruturas do domínio
    • Lista de viagens cadastradas (estrutura 1)
    • Fila de espera de participantes por viagem (estrutura 2)

#### 6.5.2.3. Descrição
Cada viagem terá um destino, uma data e um número máximo de participantes. Caso o número de interessados exceda o limite, os novos participantes entram em uma fila de espera. Para cada viagem, deve ser possível visualizar os participantes e gerenciar a fila de espera. Cada participante terá nome e CPF.

#### 6.5.2.4. MVP (Entrega única)
✅ Implementar estrutura de lista dinâmica para as viagens.

✅ Implementar estrutura de fila dinâmica para fila de espera de participantes por viagem.

✅ Funções para:

    • Cadastrar nova viagem.
    • Remover viagem.
    • Listar todas as viagens.
    • Inscrever participante na viagem (entra na fila se o limite for atingido).
    • Confirmar saída de um participante (libera vaga para o próximo da fila).
    • Buscar viagem por destino.
    • Ordenar viagens por data ou destino.

---
