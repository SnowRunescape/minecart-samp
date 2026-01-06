/*
Codico desenvolvido por Prisma_Lua. 
Contato para Suporte: prisma scripter#5238
loja vip para samp
Integrado com a API da (minecart.com.br)
*/

            // Definers
#define         MAX_MARKET_PRODUTOS         (10)

            // Includes
#include <YSI_Coding\y_hooks>

            // Forwards
forward OnMarketplace_Verificacao(Request:id, E_HTTP_STATUS:status, Node:node);
forward OnMarketplace_Ativacao(Request:id, E_HTTP_STATUS:status, Node:node);

static enum E_PRODUTO {
    E_PRODUTO_NOME[40 + 1],
    E_PRODUTO_CHAVE[20 + 1]
};

static 
    Request:marketPointer[MAX_PLAYERS],
    Request:marketPointerKey[MAX_PLAYERS],
    RequestsClient:marketPlace,
    e_Produto[MAX_PLAYERS][MAX_MARKET_PRODUTOS][E_PRODUTO];

static const
    e_MarketPlaceName[60 + 1] = "SEU_NAME",
    e_MarketPlaceToken[168 + 1] = "SEU_TOKEN";

hook OnGameModeInit() {

    marketPlace = RequestsClient("https://api.minecart.com.br/", RequestHeaders(
        "Authorization", e_MarketPlaceToken,
        "ShopServer", e_MarketPlaceName
    ));
    return true;
}



/*

                    ooooooooo.   ooooo     ooo oooooooooo.  ooooo        ooooo   .oooooo.   
                    `888   `Y88. `888'     `8' `888'   `Y8b `888'        `888'  d8P'  `Y8b  
                    888   .d88'  888       8   888     888  888          888  888          
                    888ooo88P'   888       8   888oooo888'  888          888  888          
                    888          888       8   888    `88b  888          888  888          
                    888          `88.    .8'   888    .88P  888       o  888  `88b    ooo  
                    o888o           `YbodP'    o888bood8P'  o888ooooood8 o888o  `Y8bood8P'  

*/

public OnMarketplace_Verificacao(Request:id, E_HTTP_STATUS:status, Node:node) {

    if(status != HTTP_STATUS_OK)
        return true;

    new playerid = -1;
    foreach(new i: Player) {
        if(marketPointer[i] != id)
            continue;

        playerid = i;
        break;
    }

    if(playerid == -1)
        return true;

    new Node:produtos;
    JsonGetArray(node, "products", produtos);

    new tamanho;
    JsonArrayLength(produtos, tamanho);

    if(!tamanho) {
        SendClientMessage(playerid, 0xFFFF00FF, "[LOJA]: Você não tem nenhum produto comprado");
        return true;
    }

    if(tamanho > MAX_MARKET_PRODUTOS)
        tamanho = MAX_MARKET_PRODUTOS;

    new dialog[(50 + 30) * MAX_MARKET_PRODUTOS];

    strcat(dialog, "Item\tChave\n");
    for(new i = 0; i < tamanho; i++) {
        new Node:produto;
        JsonArrayObject(produtos, i, produto);

        JsonGetString(produto, "product_name", e_Produto[playerid][i][E_PRODUTO_NOME]);
        JsonGetString(produto, "key", e_Produto[playerid][i][E_PRODUTO_CHAVE]);

        format(dialog, sizeof dialog, "%s%s\t%s\n", dialog, e_Produto[playerid][i][E_PRODUTO_NOME], e_Produto[playerid][i][E_PRODUTO_CHAVE]);
    }

    Dialog_Show(playerid, D_MARKETPLACE, DIALOG_STYLE_TABLIST_HEADERS, "Ativações", dialog, "Ativar", "Fechar");
    return true;
}

public OnMarketplace_Ativacao(Request:id, E_HTTP_STATUS:status, Node:node) {

    if(status != HTTP_STATUS_OK)
        return true;

    new playerid = -1;
    foreach(new i: Player) {
        if(marketPointerKey[i] != id)
            continue;

        playerid = i;
        break;
    }

    if(playerid == -1)
        return true;

    new Node:commands, Node:commandGroup, tamanho, item_id[30 + 1];
    JsonGetObject(node, "commands", commands);
    JsonArrayLength(commands, tamanho);

    if(!tamanho)
        return SendClientMessage(playerid, 0xFFFF00FF, "[ERRO]: Não foi possível encontrar o token id desse item");

    JsonArrayObject(commands, 0, commandGroup);
    JsonGetNodeString(commandGroup, item_id);

    new item_nome[40 + 1], quantidades;

    // Categoria Moedas 
    if(!strcmp(item_id, "1km", true)) { 
        item_nome = "1k Moedas VIP"; 
        quantidades = 1000; 
        PlayerInfo[playerid][pReceberMoedas] += quantidades;
    }
    if(!strcmp(item_id, "10km", true)) { 
        item_nome = "10k Moedas VIP"; 
        quantidades = 10000; 
        PlayerInfo[playerid][pReceberMoedas] += quantidades;
    }
    if(!strcmp(item_id, "50km", true)) { 
        item_nome = "50k Moedas VIP"; 
        quantidades = 50000; 
        PlayerInfo[playerid][pReceberMoedas] += quantidades;
    }
    if(!strcmp(item_id, "100km", true)) { 
        item_nome = "100k Moedas VIP"; 
        quantidades = 100000; 
        PlayerInfo[playerid][pReceberMoedas] += quantidades;
    }

    // Categoria Veiculos
    if(!strcmp(item_id, "infernus_inv", true)) { // Infernus
        item_nome = "Infernus de Inv"; 
        quantidades = 1; 
        AddItem(playerid, 411, quantidades);
    }
    if(!strcmp(item_id, "subaru_inv", true)) { // Subaru
        item_nome = "Subaru de Inv"; 
        quantidades = 1; 
        AddItem(playerid, 560, quantidades);
    }
    if(!strcmp(item_id, "maverick_inv", true)) { // Maverick
        item_nome = "Maverick de Inv"; 
        quantidades = 1; 
        AddItem(playerid, 487, quantidades);
    }
    if(!strcmp(item_id, "r1_inv", true)) { // R1
        item_nome = "R1 de Inv"; 
        quantidades = 1; 
        AddItem(playerid, 522, quantidades);
    }
    if(!strcmp(item_id, "sanchez_inv", true)) { // Sanchez
        item_nome = "Sanchez de Inv"; 
        quantidades = 1; 
        AddItem(playerid, 468, quantidades);
    }
    if(!strcmp(item_id, "dumper_inv", true)) { // Dumper
        item_nome = "Dumper de Inv"; 
        quantidades = 1; 
        AddItem(playerid, 406, quantidades);
    }

    // Categoria Itens
    if(!strcmp(item_id, "nick_brilhoso", true)) { // Nick Brilhoso
        item_nome = "Nick Brilhoso"; 
        quantidades = 1; 
        AddItem(playerid, 1952, quantidades);
    }
    if(!strcmp(item_id, "carro_brilhoso", true)) { // Carro Brilhoso
        item_nome = "Carro Brilhoso"; 
        quantidades = 1; 
        AddItem(playerid, 11746, quantidades);
    }
    if(!strcmp(item_id, "jet_pack", true)) { // Jet Pack
        item_nome = "Jet Pack"; 
        quantidades = 1; 
        AddItem(playerid, 370, quantidades);
    }

    // Categoria Outros
    if(!strcmp(item_id, "grana_1b", true)) { // Dinheiro
        item_nome = "Dinheiro 1 bilhao"; 
        quantidades = 1000000000; 
		ResetPlayerMoneyEx(playerid);
		GivePlayerMoneyEx(playerid, quantidades);
    }
    if(!strcmp(item_id, "produtos_1kk", true)) { // Produtos
        new faz_id =  PlayerInfo[playerid][pFazkey];
        item_nome = "Produtos Fazenda"; 
        quantidades = 1000000; 
        FazendaInfo[faz_id][fProdutos] = quantidades;
		SalvarFazenda(faz_id);
    }

    // Categoria Acessorios
    if(!strcmp(item_id, "acc_colete_cop", true)) { // Colete COP
        item_nome = "Colete COP"; 
        quantidades = 1; 
        AddItem(playerid, 19142, quantidades);
    }
    if(!strcmp(item_id, "acc_mascara_ninja", true)) { // Mascara Ninja
        item_nome = "Mascara Ninja"; 
        quantidades = 1; 
        AddItem(playerid, 19801, quantidades);
    }
    if(!strcmp(item_id, "acc_arara", true)) { // Arara
        item_nome = "Arara"; 
        quantidades = 1; 
        AddItem(playerid, 19078, quantidades);
    }
    if(!strcmp(item_id, "acc_brilho_branco", true)) { // Brilho Branco
        item_nome = "Brilho Branco"; 
        quantidades = 1; 
        AddItem(playerid, 18693, quantidades);
    }
    if(!strcmp(item_id, "acc_sniper_enfeite", true)) { // Sniper de Enfeite
        item_nome = "Sniper de Enfeite"; 
        quantidades = 1; 
        AddItem(playerid, 2036, quantidades);
    }
    if(!strcmp(item_id, "acc_m4_enfeite", true)) { // M4 de enfeite
        item_nome = "M4 de enfeite"; 
        quantidades = 1; 
        AddItem(playerid, 2035, quantidades);
    }
    if(!strcmp(item_id, "acc_efeito_fumaca", true)) { // Efeito Fumaca
        item_nome = "Efeito Fumaca"; 
        quantidades = 1; 
        AddItem(playerid, 2780, quantidades);
    }
    if(!strcmp(item_id, "acc_gas_nitro", true)) { // Gas nitro
        item_nome = "Gas nitro"; 
        quantidades = 1; 
        AddItem(playerid, 18702, quantidades);
    }
    if(!strcmp(item_id, "acc_fogueira", true)) { // Fogueira
        item_nome = "Fogueira"; 
        quantidades = 1; 
        AddItem(playerid, 19632, quantidades);
    }
    if(!strcmp(item_id, "acc_mascara_jason", true)) { // Mascara do Jason
        item_nome = "Mascara do Jason"; 
        quantidades = 1; 
        AddItem(playerid, 19036, quantidades);
    }
    if(!strcmp(item_id, "acc_fumaca_verde", true)) { // Fumaca Verde
        item_nome = "Fumaca Verde"; 
        quantidades = 1; 
        AddItem(playerid, 18729, quantidades);
    }
    if(!strcmp(item_id, "acc_touca_preta", true)) { // Touca Preta
        item_nome = "Touca Preta"; 
        quantidades = 1; 
        AddItem(playerid, 18964, quantidades);
    }
    if(!strcmp(item_id, "acc_charuto", true)) { // Charuto
        item_nome = "Charuto"; 
        quantidades = 1; 
        AddItem(playerid, 354, quantidades);
    }
    if(!strcmp(item_id, "acc_mochila", true)) { // Mochila
        item_nome = "Mochila"; 
        quantidades = 1; 
        AddItem(playerid, 3026, quantidades);
    }

    // Categoria Fichas
    if(!strcmp(item_id, "ficha_bronze", true)) { // Ficha Bronze
        item_nome = "Ficha Bronze"; 
        quantidades = 1; 
        AddItem(playerid, 1853, quantidades);
    }
    if(!strcmp(item_id, "ficha_prata", true)) { // Ficha Prata
        item_nome = "Ficha Prata"; 
        quantidades = 1; 
        AddItem(playerid, 1854, quantidades);
    }
    if(!strcmp(item_id, "ficha_ouro", true)) { // Ficha Ouro
        item_nome = "Ficha Ouro"; 
        quantidades = 1; 
        AddItem(playerid, 1855, quantidades);
    }
    if(!strcmp(item_id, "ficha_platina", true)) { // Ficha Platina
        item_nome = "Ficha Platina"; 
        quantidades = 1; 
        AddItem(playerid, 1856, quantidades);
    }

    // Categoria Caixas
    if(!strcmp(item_id, "caixa_platina", true)) { // Caixa Platina
        item_nome = "Caixa Platina"; 
        quantidades = 1; 
        AddItem(playerid, 19057, quantidades);
    }
    if(!strcmp(item_id, "caixa_wonder", true)) { // Caixa Wonder
        item_nome = "Caixa Wonder"; 
        quantidades = 1; 
        AddItem(playerid, 19058, quantidades);
    }

    SendClientMessageToAll(-1, va_return("[LOJA]: %s[%d] comprou %s no nosso marketplace digital", Marketplace_Nome(playerid), playerid, item_nome));
    return true;
}



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock Marketplace_Verificar(playerid) {

    marketPointer[playerid] = RequestJSON(
        marketPlace,
        "shop/player/mykeys",
        HTTP_METHOD_POST,
        "OnMarketplace_Verificacao",
        JsonObject(
            "username", JsonString(Marketplace_Nome(playerid))
        ),
        RequestHeaders()
    );
}

static stock Marketplace_Ativar(playerid, const key[]) {

    marketPointerKey[playerid] = RequestJSON(
        marketPlace,
        "shop/player/redeemkey",
        HTTP_METHOD_POST,
        "OnMarketplace_Ativacao",
        JsonObject(
            "username", JsonString(Marketplace_Nome(playerid)),
            "key", JsonString(key)
        ),
        RequestHeaders()
    ); 
}

static Marketplace_Nome(playerid) {

    new nome[MAX_PLAYER_NAME + 1];
    GetPlayerName(playerid, nome, sizeof nome);
    return nome;
}



/*

                    oooooooooo.   ooooo       .o.       ooooo          .oooooo.     .oooooo.     .oooooo..o 
                    `888'   `Y8b  `888'      .888.      `888'         d8P'  `Y8b   d8P'  `Y8b   d8P'    `Y8 
                    888      888  888      .8"888.      888         888      888 888           Y88bo.      
                    888      888  888     .8' `888.     888         888      888 888            `"Y8888o.  
                    888      888  888    .88ooo8888.    888         888      888 888     ooooo      `"Y88b 
                    888     d88'  888   .8'     `888.   888       o `88b    d88' `88.    .88'  oo     .d8P 
                    o888bood8P'   o888o o88o     o8888o o888ooooood8  `Y8bood8P'   `Y8bood8P'   8""88888P'  

*/

Dialog:D_MARKETPLACE(playerid, response, listitem) {

    if(response) 
        Marketplace_Ativar(playerid, e_Produto[playerid][listitem][E_PRODUTO_CHAVE]);
    
    return true;
}


CMD:resgatar(playerid) {
    Marketplace_Verificar(playerid);
    return true;
}