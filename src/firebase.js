
import { initializeApp } from "firebase/app";
import { getDatabase } from "firebase/database";
import { getAuth } from "firebase/auth";

const firebaseConfig = {
  apiKey: "AIzaSyAzPGTKuJ4bzN6Ihvz9q5D1GHjJpOZE5yY",
  authDomain: "smart-cart-189d3.firebaseapp.com",
  databaseURL: "https://smart-cart-189d3-default-rtdb.firebaseio.com/",
  projectId: "smart-cart-189d3",
  storageBucket: "smart-cart-189d3.appspot.com",
  messagingSenderId: "1234567890",
  appId: "1:1234567890:web:abcdef123456",
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
export const auth = getAuth(app);
export const database = getDatabase(app);
