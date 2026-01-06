# Minecart SAMP Integration

Sistema de integração para loja VIP de servidores SA-MP (San Andreas Multiplayer) com a API da [Minecart](https://minecart.com.br).

## 📋 Descrição

Este include permite que servidores SA-MP integrem facilmente uma loja VIP utilizando a plataforma Minecart. Com ele, os jogadores podem comprar produtos através do site e resgatar automaticamente no jogo através de comandos simples.

## ✨ Funcionalidades

- **Resgate automático de produtos** comprados na loja Minecart
- **Múltiplas categorias de produtos:**
  - 💰 Moedas VIP
  - 🚗 Veículos de inventário
  - 🎒 Itens especiais
  - 👔 Acessórios customizados
  - 🎫 Fichas (Bronze, Prata, Ouro, Platina)
  - 📦 Caixas especiais (Platina, Wonder)
  - 💵 Dinheiro in-game
  - 🌾 Produtos para fazenda
- **Sistema de verificação seguro** via API
- **Interface amigável** com diálogos no jogo
- **Listagem de produtos** disponíveis para ativação

## 📦 Dependências

- [YSI Library](https://github.com/pawn-lang/YSI-Includes) (YSI_Coding\y_hooks)
- Sistema de HTTP requests (JSON/API)
- Sistema de diálogos personalizado

## 🔧 Instalação

1. **Baixe o arquivo** `minecart.inc` e coloque na pasta `pawno/include` do seu servidor

2. **Adicione o include** no seu gamemode:
```pawn
#include <minecart>
```

3. **Configure suas credenciais** dentro do arquivo `minecart.inc`:
```pawn
static const
    e_MarketPlaceName[60 + 1] = "SEU_NAME",        // Nome da sua loja
    e_MarketPlaceToken[168 + 1] = "SEU_TOKEN";     // Token de autenticação
```

4. **Configure os IDs dos produtos** de acordo com sua loja Minecart no callback `OnMarketplace_Ativacao`

## 🚀 Como Usar

### Para Jogadores

Após comprar um produto na loja Minecart, use o comando no jogo:
```
/resgatar
```

Isso abrirá um diálogo mostrando todos os produtos disponíveis para ativação. Selecione o produto desejado e ele será automaticamente creditado na sua conta.

### Para Desenvolvedores

#### Adicionar Novos Produtos

Edite a função `OnMarketplace_Ativacao` e adicione um novo bloco:

```pawn
if(!strcmp(item_id, "seu_produto_id", true)) {
    item_nome = "Nome do Produto";
    quantidades = 1;
    // Sua lógica de entrega aqui
    AddItem(playerid, ID_DO_ITEM, quantidades);
}
```

#### Verificar Produtos Programaticamente

```pawn
Marketplace_Verificar(playerid);
```

## 📝 Exemplos de Produtos

### Moedas VIP
- `1km` - 1.000 moedas
- `10km` - 10.000 moedas
- `50km` - 50.000 moedas
- `100km` - 100.000 moedas

### Veículos
- `infernus_inv` - Infernus de Inventário
- `subaru_inv` - Subaru de Inventário
- `maverick_inv` - Maverick de Inventário
- `r1_inv` - R1 de Inventário

### Acessórios
- `acc_colete_cop` - Colete COP
- `acc_mascara_ninja` - Máscara Ninja
- `nick_brilhoso` - Nick Brilhoso
- `jet_pack` - Jet Pack

## ⚙️ Configuração da API

O sistema se conecta automaticamente à API da Minecart em:
```
https://api.minecart.com.br/
```

**Endpoints utilizados:**
- `POST /shop/player/mykeys` - Verificar produtos disponíveis
- `POST /shop/player/redeemkey` - Ativar/resgatar produto

## 🛡️ Segurança

- Todos os resgates são validados pela API da Minecart
- Cada chave (key) só pode ser usada uma vez
- Sistema de autenticação via token
- Validação de status HTTP antes de processar

## 📞 Suporte

- **Desenvolvedor Original:** Prisma_Lua
- **Discord:** prisma scripter#5238
- **Plataforma:** [Minecart](https://minecart.com.br)

Para suporte técnico relacionado à API ou configuração da loja, entre em contato através dos canais oficiais da Minecart.

## 🤝 Contribuindo

Contribuições são bem-vindas! Para contribuir:

1. Faça um fork do projeto
2. Crie uma branch para sua feature (`git checkout -b feature/NovaFuncionalidade`)
3. Commit suas mudanças (`git commit -m 'Adiciona nova funcionalidade'`)
4. Push para a branch (`git push origin feature/NovaFuncionalidade`)
5. Abra um Pull Request

### Ideias para Contribuição

- Adicionar mais categorias de produtos
- Melhorar tratamento de erros
- Adicionar logs de transações
- Criar sistema de histórico de resgates
- Implementar cooldown entre resgates
- Adicionar suporte para produtos com quantidade variável

## 📄 Licença

Consulte o arquivo [LICENSE](LICENSE) para mais informações.

## ⚠️ Notas Importantes

- Certifique-se de ter uma conta válida na Minecart
- Configure corretamente seu token e nome da loja
- Teste em ambiente de desenvolvimento antes de usar em produção
- Mantenha seu token em segurança e nunca o compartilhe
- Adapte os IDs dos produtos de acordo com sua loja

## 📊 Limitações

- Máximo de **10 produtos** por verificação (`MAX_MARKET_PRODUTOS`)
- Requer sistema de inventário compatível com `AddItem()`
- Requer sistema de player data com `PlayerInfo[]`

---

**Desenvolvido para a comunidade SA-MP** 🎮