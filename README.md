# Projeto A - Iot Aplicada

Uma empresa de varejo necessita monitorar a temperatura e umidade de seu datacenter principal. Com isso, foi contratado o serviço para desenvolver um protótipo onde pudesse ser enviado um alerta via Telegram para o setor de manutenções. E uma aplicação web, onde o setor de tecnologia também pudesse  monitorar em tempo real a temperatura e umidade da sala.

# Hardware
- ESP 32
- LED RGB
- Sensor DHT
- Resistor

# Tecnologias
- Telegram
- Wi-Fi
- Firebase
- Site


## Solução

Um sensor irá monitorar a temperatura e umidade de uma sala e enviar os dados para um WebServer. Os valores ideais são 22ºC a 26ºC de temperatura e 50% a 70% de umidade. 
Variações fora desses limites acionarão um alerta no Telegram da equipe de manutenção para ajustar o sistema de ar condicionado da sala e evitar danos aos equipamentos.

## Projeto

Clone ou baixe o projeto para seu computador, instale os pacotes através do comando:

```bash
npm install
```

Depois execute com o comando: 

```bash
npm run dev
```

Você também pode ver o projeto rodando aqui:
https://projeto-a.vercel.app/

:)