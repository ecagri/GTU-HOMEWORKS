import { db, auth} from './firebaseInit.js';
import { doc, getDoc, updateDoc, setDoc, getDocs, collection, arrayUnion } from "https://www.gstatic.com/firebasejs/9.4.0/firebase-firestore.js"

let selectedImages = [];

let user = localStorage.getItem("user")

let coefficient = 1

let nextPage = "badImageSelection.html"

async function loadImage(docSnapImage, index) {

    const image = document.createElement("img");
    image.src = docSnapImage.data().path;

    image.addEventListener('click', function () {
        toggleSelection(image, index+ ".jpg");
    });

    document.getElementById('image-container').appendChild(image);
    return Promise.resolve(); 
}

async function loadAllImages() {
    const promises = [];

    let counter = 0

    while(counter < 50){
        let index = Math.floor(Math.random() * 12728)
        const docRefImage = doc(db, "Images", index + ".jpg")
        const docSnapImage = await getDoc(docRefImage)

        if(docSnapImage.exists()){
            counter += 1
            promises.push(loadImage(docSnapImage, index))
        }
    }

    try {
        await Promise.all(promises);
        console.log('All images loaded successfully');
    } catch (error) {
        console.error('Error loading images:', error);
    }
}

loadAllImages();

function toggleSelection(image, imagename) {

    const index = selectedImages.indexOf(imagename);
    if (index === -1) {
        if (selectedImages.length < 15) {
            selectedImages.push(imagename);
            image.classList.add('selected');
        }
    } else {
        selectedImages.splice(index, 1);
        image.classList.remove('selected');
    }
}

if(document.querySelector('h1').textContent.includes("Bad") == true){
    coefficient *= -1
    nextPage = "home.html"
}

document.getElementById('submit').addEventListener('click', async function(){
    if (selectedImages.length == 15) {
        for(let i = 0; i < 15; i++){
            const docRefImage = doc(db, "Images", selectedImages[i]);
            const docSnapImage = await getDoc(docRefImage);
            if (docSnapImage.exists()) {
                let labels = docSnapImage.data().labels
                const docSnap = await getDoc(doc(db, "users", user))
                if (docSnap.exists()) {
                    let favourites = docSnap.data().favourites || {};
                    for(let j = 0; j < labels.length; j++){
                        if(favourites.hasOwnProperty(labels[j])){
                            favourites[labels[j]] += coefficient;
                        }
                    }
                    await updateDoc(doc(db, "users", user), {
                        favourites: favourites
                    })
                }
            }
        }

        window.location.href = nextPage;
    } else {
        alert('Please select exactly 15 images.');
    }
})

