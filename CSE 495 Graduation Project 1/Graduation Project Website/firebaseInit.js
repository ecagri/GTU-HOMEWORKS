import { initializeApp } from "https://www.gstatic.com/firebasejs/9.4.0/firebase-app.js";
import { getFirestore } from "https://www.gstatic.com/firebasejs/9.4.0/firebase-firestore.js"
import { getAuth } from "https://www.gstatic.com/firebasejs/9.4.0/firebase-auth.js"

const firebaseConfig = {
  apiKey: "AIzaSyC9_8BTU5UfCthLBKbwq2eRVMSUQ31fdUc",
  authDomain: "weighty-gasket-405917.firebaseapp.com",
  projectId: "weighty-gasket-405917",
  storageBucket: "weighty-gasket-405917.appspot.com",
  messagingSenderId: "445818567601",
  appId: "1:445818567601:web:93146db9f0f4addc95db90"
};
  
  const app = initializeApp(firebaseConfig);
  const db = getFirestore(app);
  const auth = getAuth(app);
  export { app, db, auth};





