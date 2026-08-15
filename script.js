let arrData = [];
let listData = [];
let stackData = [];
let queueData = [];
let treeData = [];

const operationSelect = document.getElementById('operationSelect');
const titleGroup = document.getElementById('titleGroup');
const authorGroup = document.getElementById('authorGroup');
const recordsList = document.getElementById('recordsList');
const statusAlert = document.getElementById('statusAlert');
const alertMessage = document.getElementById('alertMessage');

// Form display switch
operationSelect.addEventListener('change', () => {
    const op = operationSelect.value;
    if (op === 'insert') {
        titleGroup.style.display = 'block';
        authorGroup.style.display = 'block';
    } else {
        titleGroup.style.display = 'none';
        authorGroup.style.display = 'none';
    }
});

// Display notification instead of terminal log
function showAlert(message, isError = false) {
    statusAlert.style.display = 'block';
    statusAlert.className = `alert-banner ${isError ? 'error' : 'success'}`;
    alertMessage.textContent = message;
}

function executeOperation() {
    const op = operationSelect.value;
    const ds = document.getElementById('dsSelect').value;
    const id = parseInt(document.getElementById('bookID').value);
    const title = document.getElementById('bookTitle').value;
    const author = document.getElementById('bookAuthor').value;

    if ((op === 'insert' || op === 'delete' || op === 'search') && isNaN(id)) {
        showAlert("Please enter a valid Book ID!", true);
        return;
    }

    const book = { bookID: id, title: title, author: author };

    switch (op) {
        case 'insert':
            if (!title || !author) {
                showAlert("Please enter both Title and Author!", true);
                return;
            }
            handleInsert(ds, book);
            break;
        case 'delete':
            handleDelete(ds, id);
            break;
        case 'search':
            handleSearch(ds, id);
            break;
        case 'display':
            handleDisplay(ds);
            break;
    }
}

function handleInsert(ds, book) {
    if (ds === 'array') {
        let i = arrData.length - 1;
        arrData.push(null);
        while (i >= 0 && arrData[i].bookID > book.bookID) {
            arrData[i + 1] = arrData[i];
            i--;
        }
        arrData[i + 1] = book;
    } else if (ds === 'list') {
        listData.push(book);
        listData.sort((a, b) => a.bookID - b.bookID);
    } else if (ds === 'stack') {
        stackData.unshift(book);
    } else if (ds === 'queue') {
        queueData.push(book);
    } else if (ds.startsWith('tree')) {
        if (treeData.some(b => b.bookID === book.bookID)) {
            showAlert("Book ID already exists in tree!", true);
            return;
        }
        treeData.push(book);
        treeData.sort((a, b) => a.bookID - b.bookID);
    }
    showAlert(`Book successfully inserted into ${ds}!`);
    handleDisplay(ds);
}

function handleDelete(ds, id) {
    let index = -1;
    let targetArr = getDSArray(ds);

    index = targetArr.findIndex(b => b.bookID === id);
    if (index !== -1) {
        targetArr.splice(index, 1);
        showAlert(`Book ID ${id} deleted successfully!`);
        handleDisplay(ds);
    } else {
        showAlert(`Book ID ${id} not found!`, true);
    }
}

function handleSearch(ds, id) {
    let targetArr = getDSArray(ds);
    let found = targetArr.find(b => b.bookID === id);

    if (found) {
        showAlert(`Book found!`);
        renderCards([found]);
    } else {
        showAlert(`Book ID ${id} not found in ${ds}!`, true);
        recordsList.innerHTML = '<p class="empty-msg">No matching book found.</p>';
    }
}

function handleDisplay(ds) {
    let targetArr = getDSArray(ds);
    if (targetArr.length === 0) {
        recordsList.innerHTML = '<p class="empty-msg">No books currently stored in this data structure.</p>';
        showAlert(`Selected data structure is empty.`, true);
    } else {
        showAlert(`Displaying all books from ${ds}.`);
        renderCards(targetArr);
    }
}

function getDSArray(ds) {
    if (ds === 'array') return arrData;
    if (ds === 'list') return listData;
    if (ds === 'stack') return stackData;
    if (ds === 'queue') return queueData;
    return treeData;
}

function renderCards(books) {
    recordsList.innerHTML = '';
    books.forEach(b => {
        const card = document.createElement('div');
        card.className = 'book-card';
        card.innerHTML = `
            <h4>ID: ${b.bookID}</h4>
            <p><strong>Title:</strong> ${b.title}</p>
            <p><strong>Author:</strong> ${b.author}</p>
        `;
        recordsList.appendChild(card);
    });
}