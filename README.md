# 🌀 Vulkan Smoke Test

Este é um utilitário simples de *smoke test* (teste rápido) para verificar
se o ambiente Vulkan está corretamente instalado e funcionando em seu sistema.

O projeto era originalmente mantido dentro do repositório Vulkan-Tools até
a versão 1.1.70, quando foi removido. Este repositório busca preservar
e manter o `vulkan-smoketest` de forma independente.

## 🎯 Objetivo

O `vulkan-smoketest` é uma ferramenta minimalista que inicializa uma instância
Vulkan, verifica extensões e tenta criar um dispositivo lógico. Seu propósito
é confirmar se a pilha Vulkan está funcional — útil especialmente para
distribuições, ambientes live, ou validação após instalação de drivers.

## 🧩 Compatibilidade

* ✅ Testado no Vulkan SDK 1.2.176.1
* 🔄 Compatível com Vulkan SDK 1.0+
* 🧰 Compiladores: GCC, Clang, MSVC

## 🛠️ Compilação

### Requer:

* Vulkan SDK instalado (ou headers e loader do Vulkan disponíveis no sistema)
* CMake

```bash
git clone https://github.com/seu-usuario/vulkan-smoketest.git
cd vulkan-smoketest
mkdir build && cd build
cmake ..
make
```

## ▶️ Uso

Após a compilação:

```bash
./vulkan-smoketest
```

Saída esperada: uma lista de informações básicas da instância Vulkan e o
resultado da criação de um dispositivo lógico.

```text
vulkan-smoketest: Vulkan instance created successfully.
Physical device: AMD RADV NAVI23
Queue family 0 supports graphics.
Logical device created and queue retrieved.
Smoke test passed!
```

## 📜 Licença

Este projeto está licenciado sob a [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.html).

## 🕰️ Histórico

* 📌 Originalmente parte de [KhronosGroup/Vulkan-Tools](https://github.com/KhronosGroup/Vulkan-Tools)
* ❌ Removido após a versão 1.1.70
* ♻️ Projeto resgatado e mantido independentemente por **`LinuxDicasPro`**

## 🤝 Contribuições

Contribuições são bem-vindas para manter a compatibilidade com novas versões
do Vulkan SDK, melhorar diagnósticos ou facilitar integração com sistemas
automatizados de testes.
