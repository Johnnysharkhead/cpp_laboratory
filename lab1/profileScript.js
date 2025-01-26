document.addEventListener('DOMContentLoaded', function() {
    let token = localStorage.getItem('token');
    
    function showUserProfile() {
        let userData = serverstub.getUserDataByToken(token);
        if(userData.success) {
            document.getElementById('userData').innerHTML = `
                <p><strong>Email:</strong> ${userData.data.email}</p>
                <p><strong>First Name:</strong> ${userData.data.firstname}</p>
                <p><strong>Last Name:</strong> ${userData.data.familyname}</p>
                <p><strong>Gender:</strong> ${userData.data.gender}</p>
                <p><strong>City:</strong> ${userData.data.city}</p>
                <p><strong>Country:</strong> ${userData.data.country}</p>
            `;
        } else {
            alert("Failed to retrieve user data: " + userData.message);
        }
    }

    function sendMessage() {
        const content = document.getElementById('newMessage').value;
        const result = serverstub.postMessage(token, content);
        if (result.success) {
            document.getElementById('newMessage').value = '';
            loadMessages();
        } else {
            alert("Failed to send message: " + result.message);
        }
    }
    
    function loadMessages() {
        const messages = serverstub.getUserMessagesByToken(token);
        if (messages.success) {
            displayMessages(messages.data, 'messages');
        } else {
            alert("Failed to load messages: " + messages.message);
        }
    }

    function searchUser() {
        const email = document.getElementById('userEmail').value;
        const userData = serverstub.getUserDataByEmail(token, email);
        if (userData.success) {
            displayUserProfile(userData.data, 'browseUserData');
            document.getElementById('browseUserProfile').style.display = 'block';
            loadUserMessages(email);
        } else {
            alert("User not found: " + userData.message);
        }
    }
    
    function displayUserProfile(userData, elementId) {
        document.getElementById(elementId).innerHTML = `
            <p><strong>Email:</strong> ${userData.email}</p>
            <p><strong>First Name:</strong> ${userData.firstname}</p>
            <p><strong>Last Name:</strong> ${userData.familyname}</p>
            <p><strong>Gender:</strong> ${userData.gender}</p>
            <p><strong>City:</strong> ${userData.city}</p>
            <p><strong>Country:</strong> ${userData.country}</p>
        `;
    }

    function displayMessages(messages, elementId) {
        const messagesHtml = messages.map(msg => `<p><strong>${msg.writer}</strong>: ${msg.content}</p>`).join('');
        document.getElementById(elementId).innerHTML = messagesHtml;
    }
    
    function loadUserMessages(email) {
        const messages = serverstub.getUserMessagesByEmail(token, email);
        if (messages.success) {
            displayMessages(messages.data, 'browseMessages');
        } else {
            alert("Failed to load messages: " + messages.message);
        }
    }
    
    function sendBrowseMessage() {
        const email = document.getElementById('userEmail').value;
        const content = document.getElementById('browseNewMessage').value;
        const result = serverstub.postMessage(token, content, email);
        if (result.success) {
            document.getElementById('browseNewMessage').value = '';
            loadUserMessages(email);
        } else {
            alert("Failed to send message: " + result.message);
        }
    }

    function changePassword(event) {
        event.preventDefault();
        let oldPassword = document.getElementById('oldPassword').value;
        let newPassword = document.getElementById('newPassword').value;
        let result = serverstub.changePassword(token, oldPassword, newPassword);
        if (result.success) {
            alert("Password changed successfully!");
            document.getElementById('changePasswordForm').reset();
        } else {
            alert("Failed to change password: " + result.message);
        }
    }

    function logOut() {
        let response = serverstub.signOut(token);
        if(response.success) {
            localStorage.removeItem('token');
            window.location.href = "client.html";
        } else {
            alert("Log out failed: " + response.message);
        }
    }

    // 初始化
    showUserProfile();
    loadMessages();

    // 事件监听器
    document.getElementById('logoutButton').addEventListener('click', logOut);
    document.querySelector('#account form').addEventListener('submit', changePassword);
    document.getElementById('sendButton').addEventListener('click', sendMessage);
    document.getElementById('refreshButton').addEventListener('click', loadMessages);
    document.getElementById('searchUser').addEventListener('click', searchUser);
    document.getElementById('browseSendButton').addEventListener('click', sendBrowseMessage);
    document.getElementById('browseRefreshButton').addEventListener('click', () => {
        const email = document.getElementById('userEmail').value;
        loadUserMessages(email);
    });
});

document.querySelectorAll('.tab').forEach(tab => {
    tab.addEventListener('click', () => {
        document.querySelectorAll('.tab, .panel').forEach(el => el.classList.remove('active'));
        tab.classList.add('active');
        document.getElementById(tab.dataset.panel).classList.add('active');
    });
});
