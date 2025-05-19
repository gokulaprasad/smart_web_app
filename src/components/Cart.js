import React, { useEffect, useState } from "react";
import { database } from "../firebase";
import { ref, onValue } from "firebase/database";

function Cart() {
  const [cartItems, setCartItems] = useState([]);

  useEffect(() => {
    const cartRef = ref(database, "ScannedRFID/");
    onValue(cartRef, (snapshot) => {
      const data = snapshot.val();
      const items = [];
      for (const key in data) {
        items.push({ id: key, status: data[key] });
      }
      setCartItems(items);
    });
  }, []);

  return (
    <div>
      <h1>Your Cart</h1>
      {cartItems.length > 0 ? (
        <ul>
          {cartItems.map((item) => (
            <li key={item.id}>
              RFID: {item.id}, Status: {item.status}
            </li>
          ))}
        </ul>
      ) : (
        <p>No items in your cart.</p>
      )}
    </div>
  );
}

export default Cart;
