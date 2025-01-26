function validateSignupForm() {
    const password = document.getElementById('signup-password').value;
    const repeatPassword = document.getElementById('repeat password').value;
    const minLength = 8; 
    
    const feedbackArea = document.getElementById('signup-feedback');
    
    if (password.length < minLength) {
        feedbackArea.textContent = `You have to set the password more than ${minLength} digits`;
        return false;
    }

    if (password !== repeatPassword) {
        feedbackArea.textContent = 'The password do not match';
        return false;
    }
    
    else{
        feedbackArea.textContent = 'Successfully signed up';
        return true;
    }

}

function submitSignup(){
    const email = document.getElementById('signup-username').value;
    const password = document.getElementById('signup-password').value;
    const firstname = document.getElementById('First name').value;
    const familyname = document.getElementById('Family name').value;
    const gender = document.getElementById('gender').value;
    const city = document.getElementById('city').value;
    const country = document.getElementById('country').value;

    if(validateSignupForm() === false) {
        return false;
    }

    const inputObject = {
        email, password, firstname, familyname, gender, city, country
    };

    const result = serverstub.signUp(inputObject);
    const feedbackArea = document.getElementById('signup-feedback');
    feedbackArea.textContent = result.message;

    return result.success;
}

function submitLogin(event) {
    event.preventDefault(); // 阻止表单默认提交行为

    const feedbackArea = document.getElementById('login-feedback');
    const email = document.getElementById('login-username').value;
    const password = document.getElementById('login-password').value;

    const result = serverstub.signIn(email, password);

    feedbackArea.textContent = result.message;

    // if the user is signed-in then a token exists at client-side representing the signed-in user
    if (result.success) { // using a web storage facility as part of HTML5
        localStorage.setItem('token', result.data); // [serverstub] return {"success": true, "message": "Successfully signed in.", "data": token};
        localStorage.setItem('email', email);
        window.location.href = 'profileView.html';
        // showTab('Home');
    }
    else {
        alert("Failed to log in: " + result.message);
    }
}

const token = localStorage.getItem('token');

if (token) {
    localStorage.setItem('token', token);
} else {
    
}