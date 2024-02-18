import {signInWithEmailAndPassword } from "https://www.gstatic.com/firebasejs/9.4.0/firebase-auth.js"
import {app, db, auth} from './firebaseInit.js'
import { doc, getDoc, setDoc, getDocs, collection } from "https://www.gstatic.com/firebasejs/9.4.0/firebase-firestore.js"

document.addEventListener('DOMContentLoaded', function () {
    const form = document.querySelector('form');

    form.addEventListener('submit', async function (event) {
        event.preventDefault(); 
        console.log("hey")
        const emailInput = document.getElementById('email');
        const passwordInput = document.getElementById('password');
        
        signInWithEmailAndPassword(auth, emailInput.value, passwordInput.value)
        .then((userCredential) => {
            const user = userCredential.user;
            localStorage.setItem("user", emailInput.value)
            window.location.href = "home.html"
        })
        .catch((error) => {
            const errorCode = error.code;
            const errorMessage = error.message;
            alert("Invalid email or password!");
        });
    }); 
});