'use client'
import { initializeApp } from 'firebase/app';
import { getDatabase } from 'firebase/database';

const firebaseConfig = {
  apiKey: "AIzaSyDziPSAgb1QUvBek2SbZohJ0cZx89sY9kY",
  authDomain: "projeto-a-d1cbc.firebaseapp.com",
  databaseURL: "https://projeto-a-d1cbc-default-rtdb.firebaseio.com",
  projectId: "projeto-a-d1cbc",
  storageBucket: "projeto-a-d1cbc.appspot.com",
  messagingSenderId: "639884288178",
  appId: "1:639884288178:web:5f9f026a0b20da45baa9ab"
};

const fire = initializeApp(firebaseConfig);
const db = getDatabase(fire);

export { fire, db };