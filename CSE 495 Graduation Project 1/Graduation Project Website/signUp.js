import {createUserWithEmailAndPassword } from "https://www.gstatic.com/firebasejs/9.4.0/firebase-auth.js"
import {app, db, auth} from './firebaseInit.js'
import { doc, getDoc, setDoc, getDocs, collection } from "https://www.gstatic.com/firebasejs/9.4.0/firebase-firestore.js"


document.addEventListener('DOMContentLoaded', async function () {

    const favourites = {}

    const favouritesCollection = await getDocs(collection(db, "Labels"));
    await favouritesCollection.forEach((doc) => {
        favourites[doc.id] = 0;
    });

    const form = document.querySelector('form');

    form.addEventListener('submit', async function (event) {
        event.preventDefault(); 

        const emailInput = document.getElementById('email');
        const passwordInput = document.getElementById('new-password');

        try {
            await validateEmail(emailInput.value);
            await validatePassword(passwordInput.value);
            const docRef = doc(db, "users", emailInput.value);
            const docSnap = await getDoc(docRef);
            if (docSnap.exists()) {
                throw new Error("The user already exists!");
            }
            
            createUserWithEmailAndPassword(auth, emailInput.value, passwordInput.value)
            .then(async (userCredential) => {
                const user = userCredential.user;
                await setDoc(doc(db, "users", emailInput.value), {
                    favourites: favourites,
                    likes: [],
                    dislikes: [],
                    shown: []
                  });
                localStorage.setItem("user", emailInput.value)
                window.location.href = "imageSelection.html"
            })
            .catch((error) => {
                const errorCode = error.code;
                const errorMessage = error.message;
            });
            
        } catch (error) {
            alert(error.message || 'Invalid email or password. Please check your inputs.');
        }
    });

    function validateEmail(email) {
        return new Promise((resolve, reject) => {
            const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
            if (emailRegex.test(email)) {
                resolve();
            } else {
                reject(new Error('Invalid email format'));
            }
        });
    }

    function validatePassword(password) {
        return new Promise((resolve, reject) => {
            if (password.length >= 8) {
                resolve();
            } else {
                reject(new Error('Password must be at least 8 characters long'));
            }
        });
    }
});

