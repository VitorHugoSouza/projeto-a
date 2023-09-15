'use client';
import React, { useEffect, useState } from 'react';
import { db } from 'services/firebase';
import { ref, onValue} from "firebase/database";


import './Monitoramento.css';

export default function Monitoramento() {

	const [dadosPlaca1, setDadosPlaca1] = useState([]);
	const [dadosPlaca2, setDadosPlaca2] = useState([]);

	function getPlaca1() {
		const distanciaRef = ref(db, 'placa-1');
		
		return onValue(distanciaRef, (placa) => {
			if(placa.exists()) {
				console.log('placa1 atualizada ==>', placa.val());
				setDadosPlaca1(placa.val());
			}
		});
	}	

	function getPlaca2() {
		const distanciaRef = ref(db, 'placa-2');
		
		return onValue(distanciaRef, (placa) => {
			if(placa.exists()) {
				console.log('placa2 atualizada ==>', placa.val());
				setDadosPlaca2(placa.val());
			}
		});
	}	
	
	useEffect(() => {

		getPlaca1();
		getPlaca2();

  }, []);

	return (
		<div>

			{/* <h3>Bem vindo ao sistema de monitoramento online!</h3>

			<div style={{ marginTop: '30px'}}>	

				<h3>Placa primária </h3>	

				<Row gutter={16}>


					<Col span={8}>
						<Card style={{ width: 300 }} bordered={true}>
							<Meta
								avatar={<FormOutlined />}
								title="Controle de volume"
								style={{ marginBottom: '10px' }}
							/>

							{dadosPlaca1.distancia <= 5 ? <p style={{ color: 'red' }}><b>Volume inferior a 5 m³. Nivel crítico!</b></p> : <p style={{ color: 'green' }}>Volume em bom nível!</p>}

						</Card>
					</Col>

					<Col span={8}>
						<Card style={{ width: 300 }} bordered={true}>
							<Meta
								avatar={<BulbOutlined />}
								title="Estado lâmpada"
								style={{ marginBottom: '10px' }}
							/>

							{dadosPlaca1.luminosidade >= 750 ? 
								<p style={{ color: 'green' }}>Lâmpada acesa. Temperatura controlada!</p>							
								:
								<p style={{ color: 'red' }}>Lâmpada apagada. Verifique a placa!</p> 
							}
							

						</Card>
					</Col>

					<Col span={8}>
						<Card style={{ width: 300 }} bordered={true}>
							<Meta
								avatar={<RedoOutlined />}
								title="Volume Atual"
								style={{ marginBottom: '10px' }}
							/>

							<p>Volume em {dadosPlaca1.distancia}m³.</p>

						</Card>
					</Col>

				</Row>
			</div>

			<Divider />

			<div style={{ marginTop: '30px'}}>	

				<h3>Placa secundária</h3>		

				<Row gutter={16}>


					<Col span={8}>
						<Card style={{ width: 300 }} bordered={true}>
							<Meta
								avatar={<FormOutlined />}
								title="Controle de volume"
								style={{ marginBottom: '10px' }}
							/>

							{dadosPlaca2.distancia <= 5 ? <p style={{ color: 'red' }}><b>Volume inferior a 5 m³. Nivel crítico!</b></p> : <p style={{ color: 'green' }}>Volume em bom nível!</p>}

						</Card>
					</Col>

					<Col span={8}>
						<Card style={{ width: 300 }} bordered={true}>
							<Meta
								avatar={<BulbOutlined />}
								title="Estado lâmpada"
								style={{ marginBottom: '10px' }}
							/>

							{dadosPlaca2.luminosidade <= 100 ? 
								<p style={{ color: 'green' }}>Lâmpada acesa. Temperatura controlada!</p>							
								:
								<p style={{ color: 'red' }}>Lâmpada apagada. Verifique a placa!</p> 
							}
							

						</Card>
					</Col>

					<Col span={8}>
						<Card style={{ width: 300 }} bordered={true}>
							<Meta
								avatar={<RedoOutlined />}
								title="Volume Atual"
								style={{ marginBottom: '10px' }}
							/>

							<p>Volume em {dadosPlaca2.distancia}m³.</p>

						</Card>
					</Col>

				</Row>
			</div>	 */}	

		</div>
	);
}