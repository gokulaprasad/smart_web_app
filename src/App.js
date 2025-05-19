// src/App.js
import React from "react";
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import Login from "./components/Login";
import Cart from "./components/Cart";

const App = () => {
  return (
    <Router>
      <div>
        <h1>Smart Cart</h1>
        <Routes>
          <Route path="/login" element={<Login />} />
          <Route path="/cart" element={<Cart />} />
        </Routes>
      </div>
    </Router>
  );
};

export default App;
