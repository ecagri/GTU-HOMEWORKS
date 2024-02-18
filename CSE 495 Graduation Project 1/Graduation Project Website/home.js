import { db, auth} from './firebaseInit.js';
import { doc, getDoc, setDoc, getDocs, collection } from "https://www.gstatic.com/firebasejs/9.4.0/firebase-firestore.js"
import { signInAnonymously } from "https://www.gstatic.com/firebasejs/9.4.0/firebase-auth.js";


const user = localStorage.getItem("user")

const docRefUser = doc(db, "users", user);
const docSnapUser = await getDoc(docRefUser);
const favourites = new Map(Object.entries(docSnapUser.data().favourites));
const likes = docSnapUser.data().likes
const dislikes = docSnapUser.data().dislikes
const shown = docSnapUser.data().shown
let favouritesArray = [...favourites.entries()];


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

async function update(likes, dislikes, favourites, shown){
    const favouritesObject = {};
    favourites.forEach((value, key) => {
      favouritesObject[key] = value;
    });

    await setDoc(doc(db, "users", user), {
        favourites: favouritesObject,
        likes: likes,
        dislikes: dislikes,
        shown: shown
    });    
}


getUserTags()

async function getUserTags(){
    favouritesArray.sort((a, b) => b[1] - a[1]);

    const top3Tags = favouritesArray.slice(0, 3);
    const last3Tags = favouritesArray.slice(-3);

    
    document.getElementById('Tag1Like').textContent = top3Tags[0][0];
    document.getElementById('Tag2Like').textContent = top3Tags[1][0];
    document.getElementById('Tag3Like').textContent = top3Tags[2][0];

    document.getElementById('Tag1Dislike').textContent = last3Tags[0][0];
    document.getElementById('Tag2Dislike').textContent = last3Tags[1][0];
    document.getElementById('Tag3Dislike').textContent = last3Tags[2][0];

    
    const circle = document.getElementById('progress-circle');
    const text = document.getElementById('percentage-text');
    const circumference = 2 * Math.PI * 40; 

    const percent = likes.length + dislikes.length == 0 ? 0 : likes.length / (likes.length + dislikes.length)
    const offset = circumference - (percent / 100) * circumference;
    circle.style.strokeDashoffset = offset;
    text.textContent = Math.round(percent * 100) + '%';
}

let current_image = await selectImage()

await loadImage(current_image)

document.getElementById('like-btn').addEventListener('click', async function(){
    likes.push(current_image)
    for(let i = 0; i < images.get(current_image).labels.length; i++){
        if(favourites.get(images.get(current_image).labels[i]) != undefined){
            favourites.set(images.get(current_image).labels[i],favourites.get(images.get(current_image).labels[i]) + Math.log(favourites.get(images.get(current_image).labels[i]) + 1)/20);
        }else{
            favourites.set(images.get(current_image).labels[i], Math.random())
        }
    }

    shown.push(current_image + ": liked")

    favouritesArray = [...favourites.entries()]

    current_image = await selectImage();

    await loadImage(current_image)

    getUserTags()

    update(likes, dislikes, favourites, shown)

});

document.getElementById('dislike-btn').addEventListener('click', async function(){
    dislikes.push(current_image)
    for(let i = 0; i < images.get(current_image).labels.length; i++){
        if(favourites.get(images.get(current_image).labels[i]) != undefined){
            favourites.set(images.get(current_image).labels[i], favourites.get(images.get(current_image).labels[i]) - 1);
        }else{
            favourites.set(images.get(current_image).labels[i], -1)
        }
    }

    shown.push(current_image + ": disliked")

    favouritesArray = [...favourites.entries()]

    current_image = await selectImage();

    await loadImage(current_image)

    getUserTags()

    update(likes, dislikes, favourites, shown)
});

document.getElementById('info-btn').addEventListener('click', function(){
    if(!document.getElementById("centered-image").hidden){
        document.getElementById('progress-container').hidden = true;
        document.getElementById("centered-image").style.transform = 'rotateY(90deg)';
        document.getElementById("centered-image").addEventListener("transitionend", transitionend);
        
    }
    else{
        document.getElementById("contents_table").style.transform = 'rotateY(0deg)';
        document.getElementById("contents_table").addEventListener("transitionend", transitionend2)
        document.getElementById('progress-container').hidden = false;
    }
});


async function loadImage(image){
    
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


async function selectImage(){
    favouritesArray.sort((a, b) => b[1] - a[1]);
    let UnionSet = new Set()
    let k_start = 0
    while(UnionSet.size == 0){
        for(let i = k_start; i < k_start + 30 && favouritesArray[i][1] > 0; i++){
            const docRef = doc(db, "Labels", favouritesArray[i][0]);
            const docSnap = await getDoc(docRef);
            if(docSnap.exists()){
                let images = docSnap.data().images;
                for(let j = 0; j < images.length; j++){
                    UnionSet.add(images[j])
                }
            }
        }
        for(let image of UnionSet){
            if(likes.indexOf(image) != -1 || dislikes.indexOf(image) != -1){
                UnionSet.delete(image)
            }
        }
        k_start += 15
    }

    let max = Number.NEGATIVE_INFINITY;
    let max_image = ""
    for(let image of UnionSet){
        let labels = images.get(image).labels  

        let current = 0
        for(let j = 0; j < labels.length; j++){
            if(favourites.get(labels[j]) != undefined){
                current += favourites.get(labels[j]);
            }
        }
        if(current != 0){
            current = current/labels.length
        }
        if(current > max){
            max = current;
            max_image = image 
        }
    }
    document.getElementById("point").textContent = max.toFixed(2);
    document.getElementById("number_of_images").textContent = UnionSet.size
    document.getElementById("liked").textContent = likes.length
    document.getElementById("disliked").textContent = dislikes.length
    
    return max_image
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
        if(favourites.get(labels[i]) != undefined){
            cell.innerHTML += favourites.get(labels[i]).toFixed(2)
        }else{
            cell.innerHTML += 0;
        }
        if (i + 1 < labels.length) {
            cell1.innerHTML = labels[i + 1] + " ";
            if(favourites.get(labels[i + 1]) != undefined){
                cell1.innerHTML += favourites.get(labels[i + 1]).toFixed(2);
            }else{
                cell1.innerHTML += 0;
    
            }
        }
    }
}
