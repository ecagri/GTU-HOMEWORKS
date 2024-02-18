import { db, auth} from './firebaseInit.js';
import { doc, getDoc, setDoc, getDocs, collection } from "https://www.gstatic.com/firebasejs/9.4.0/firebase-firestore.js"
import { signInAnonymously } from "https://www.gstatic.com/firebasejs/9.4.0/firebase-auth.js";

const favourites = []

let current_image = 0;

const shown = [];

const favouritesCollection = await getDocs(collection(db, "Labels"));
await favouritesCollection.forEach((doc) => {
    favourites.push({key: doc.id, volume: 0});
});

var listContainer = document.getElementById('list-container');

let images = localStorage.getItem("images")

if(images == null){
    images = new Map();

    const imageCollection = await getDocs(collection(db, "Images"));
    imageCollection.forEach((doc) => {
        images.set(doc.id, doc.data())
    });

    localStorage.setItem("images", JSON.stringify(Array.from(images.entries())));
}else{
    images = new Map(JSON.parse(localStorage.getItem("images")));
}

// Populate the list
favourites.forEach(function (item) {
    var listItem = document.createElement('div');
    listItem.className = 'list-item';

    var keyElement = document.createElement('span');
    keyElement.textContent = item.key;

    var volumeSlider = document.createElement('input');
    volumeSlider.type = 'range';
    volumeSlider.value = item.volume;
    volumeSlider.min = 0;
    volumeSlider.max = 10;
    volumeSlider.className = 'volume-slider';

    var volumeValue = document.createElement('span');
    volumeValue.className = 'volume-value';
    volumeValue.textContent = item.volume;

    // Add an event listener to track changes in the volume slider
    volumeSlider.addEventListener('input', function (event) {
        var value = parseInt(event.target.value, 10);
        item.volume = value;
        volumeValue.textContent = value; // Update the displayed value
    });

    listItem.appendChild(keyElement);
    listItem.appendChild(volumeSlider);
    listItem.appendChild(volumeValue);

    listContainer.appendChild(listItem);

});

document.getElementById("search-btn").addEventListener('click', async function(){
    current_image = await selectImage()

    await loadImage(current_image)
    
})

async function selectImage(){

    const favouritesArray = favourites.sort((a, b) => b.volume - a.volume);

    let UnionSet = new Set()
    let k_start = 0
    while(UnionSet.size == 0){
        for(let i = k_start; i < k_start + 30; i++){
            const docRef = doc(db, "Labels", favouritesArray[i].key);
            const docSnap = await getDoc(docRef);
            if(docSnap.exists()){
                let images = docSnap.data().images;
                for(let j = 0; j < images.length; j++){
                    if(!shown.includes(images[j]))
                        UnionSet.add(images[j])
                }
            }
            
        }
        k_start += 15
    }

    let points = {}
    for(let image of UnionSet){
        let labels = images.get(image).labels  

        let current = 0
        for(let j = 0; j < labels.length; j++){
            let item = favourites.find(item => item.key === labels[j]);
            if(item){
                current += item.volume
            }
        }

        points[image] = current;
    }

    const maxValues = Object.values(points);
    const maxValue = Math.max(...maxValues);
    const keysWithMaxValue = Object.keys(points).filter(key => points[key] === maxValue);

    return keysWithMaxValue[Math.floor(Math.random() * (keysWithMaxValue.length - 1))];
}


document.getElementById('info-btn').addEventListener('click', function(){
    if(!document.getElementById("centered-image").hidden){
        document.getElementById("centered-image").style.transform = 'rotateY(90deg)';
        document.getElementById("centered-image").addEventListener("transitionend", transitionend);
        
    }
    else{
        document.getElementById("contents_table").style.transform = 'rotateY(0deg)';
        document.getElementById("contents_table").addEventListener("transitionend", transitionend2)
    }
});

async function transitionend(){
    document.getElementById("centered-image").hidden = true;
    document.getElementById("contents_table").hidden = false;  
    await new Promise(resolve => setTimeout(resolve, 300));
    document.getElementById("contents_table").style.transform = 'rotateY(-90deg)';
    document.getElementById("centered-image").removeEventListener("transitionend", transitionend)
}

async function transitionend2(){
    document.getElementById("contents_table").hidden = true;
    document.getElementById("centered-image").hidden = false;    
    await new Promise(resolve => setTimeout(resolve, 300));
    document.getElementById("centered-image").style.transform = 'rotateY(0deg)';
    document.getElementById("contents_table").removeEventListener("transitionend", transitionend2)
}


async function loadImage(image){
    shown.push(image)
    if(!document.getElementById("centered-image").hidden){
        document.getElementById("centered-image").style.transform = 'rotateY(90deg)';
        document.getElementById("centered-image").addEventListener("transitionend", function(){
            document.getElementById("centered-image").setAttribute('src', images.get(image).path);
            document.getElementById("centered-image").onload = function(){
                document.getElementById("centered-image").style.transform = 'rotateY(0deg)';
            }
        });

        await getImageTags(favourites)

    }else{
        document.getElementById("contents_table").style.transform = 'rotateY(0deg)';
        document.getElementById("contents_table").addEventListener("transitionend", async function(){
            document.getElementById("centered-image").setAttribute('src', images.get(image).path);
            await getImageTags(favourites)
            document.getElementById("contents_table").style.transform = 'rotateY(-90deg)';
        });
    }
}

async function getImageTags(favourites){
    var table = document.getElementById("contents_table");
    while (table.rows.length > 1) {
        table.deleteRow(table.rows.length - 1);
    }

    const labels = images.get(current_image).labels
    for (let i = 0; i < labels.length; i += 2) {
        var row = table.insertRow();
        var cell = row.insertCell(0);
        var cell1 = row.insertCell(1);
        cell.innerHTML = labels[i] + " ";
    
        if (i + 1 < labels.length) {
            cell1.innerHTML = labels[i + 1] + " ";
        }
    }

}