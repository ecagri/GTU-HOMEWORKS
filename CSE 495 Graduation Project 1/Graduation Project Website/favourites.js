import { db, auth} from './firebaseInit.js';
import { doc, getDoc, setDoc, getDocs, collection } from "https://www.gstatic.com/firebasejs/9.4.0/firebase-firestore.js"
import { signInAnonymously } from "https://www.gstatic.com/firebasejs/9.4.0/firebase-auth.js";

const user = localStorage.getItem("user")

const docRefUser = doc(db, "users", user);
const docSnapUser = await getDoc(docRefUser);
const favourites = new Map(Object.entries(docSnapUser.data().favourites));
let favouritesArray = [...favourites.entries()];
favouritesArray.sort((a, b) => b[1] - a[1]);


var data = {
    labels: [],
    datasets: [{
      label: 'YOUR FAVOURITE TAGS',
      data: [],
      backgroundColor: 'rgba(75, 192, 192, 0.2)', 
      borderColor: 'rgba(75, 192, 192, 1)', 
      borderWidth: 1
    }]
};

for(let i = 0; i < 20; i++){
    data.labels.push(favouritesArray[i][0]);
    data.datasets[0].data.push(favouritesArray[i][1])

}


var ctx = document.getElementById('myHistogram').getContext('2d');

var myHistogram = new Chart(ctx, {
    type: 'bar',
    data: data,
    options: {
      scales: {
        y: {
          beginAtZero: true
        }
      }
    }
});