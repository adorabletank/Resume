// Name : Seungmoon Lee
// ID   : 164830218
// Email: slee544@myseneca.ca
// Course: WEB322 NII

////cyclic link: https://app.cyclic.sh/#/deploy/adorabletank/web-ass6

const exp = require("express") 
const app = exp();
const path = require("path");
const bodyParser = require("body-parser");
const handlebars = require("express-handlebars");
const mongoose = require("mongoose");
const clientSessions = require("client-sessions");
const bcrypt = require('bcryptjs');

const registration = mongoose.createConnection("mongodb+srv://seung:Eurekarenton92@atlascluster.zeem57y.mongodb.net/web322_week8?retryWrites=true&w=majority");
const blog = mongoose.createConnection        ("mongodb+srv://seung:Eurekarenton92@atlascluster.zeem57y.mongodb.net/web322_week8?retryWrites=true&w=majority");


const registration_schema = new mongoose.Schema({
    "firstname": String,
    "lastname": String,
    "username": { "type": String, "unique": true },
    "password": String,
    "address": String,
    "dob": String,
    "phoneD": String,
    "course": String,
    "email": { "type": String, "unique": true }
});

const blog_schema = new mongoose.Schema({
    "title": String,
    "date": String,
    "content": String,
    "image" : String
});

const user_info = registration.model("registration", registration_schema);
const blog_content = blog.model("blog", blog_schema);


app.engine(".hbs", handlebars.engine({extname: '.hbs'}));
app.set('view engine', '.hbs');
app.use(bodyParser.urlencoded({extended: true}));

app.use(clientSessions({
    cookieName: "session", 
    secret: "assignment_6_web322_guess", 
    duration: 5 * 60 * 1000, 
    activeDuration: 1000 * 60 
  }));


app.get("/", function(req, res) {
    blog_content.find().exec().then((data) =>{
        let blogData = new Array;
        data.forEach(element => {
            blogData.push({
                title: element.title,
                date: element.date,
                content: element.content,
                image: element.image
            });
        });
        res.render("blog", { admData: blogData, layout: false});
    });
});

app.get("/article", function(req, res) {
    res.render("read_more", {layout: false});
});

app.post("/article", function(req, res) {
    blog_content.findOne({ title: req.body.title }).exec().then((data) =>{
        if(data) 
        {
         res.render("read_more", {id:data._id, title:data.title, content:data.content, date:data.date, image:data.image, layout: false});
        }
        else
        {
         res.render("blog", {errors: "not able to bring article",layout: false});
        }
     });
});

app.post("/update_article", ensureLogin, function(req, res){
    blog_content.updateOne({
        _id : req.body.UpdateID
    },
    {$set: {
        title: req.body.title,
        date : req.body.date,
        content: req.body.content,
        image : req.body.image
    
     }}).exec();

    res.redirect("/");
});

app.get("/registration", function(req, res) {
    res.render("registration", {layout: false});
});

function dateOfBirth(birth) 
{
    const dofb = /^\d{2}-\d{2}-\d{4}$/;
    return dofb.test(birth); 
}

function phoneNum(num) 
{
    const phone = /^\d{3}-\d{3}-\d{4}$/;
    return phone.test(num); 
}


app.post("/registration", function(req, res){
    var registrationData = {
        firstname: req.body.firstname,
        lastname: req.body.lastname,
        username: req.body.username,
        password: req.body.password,
        address: req.body.address,
        dob: req.body.dob,
        phoneD: req.body.phoneD,
        course: req.body.course,
        email: req.body.email
    }

    if(registrationData.username == "" || registrationData.password == "" || registrationData.dob == "" || registrationData.phoneD == "")
    {
        var regiError = "The field with * should be entered!!!";
        res.render("registration", { regiError: regiError, data: registrationData, layout: false });
        return;
    }
    else if(dateOfBirth(registrationData.dob) != true)
    {
        var dobError = "Follow the format dd-mm-yyyy, include -";
        res.render("registration", { dobError: dobError, data: registrationData, layout: false });
    }
    else if(phoneNum(registrationData.phoneD) != true)
    {
        var phoneError = "Follow the format 123-456-7890, include -";
        res.render("registration", { phoneError: phoneError, data: registrationData, layout: false });
    }
    else if(registrationData.password.length < 6 || registrationData.password.length > 12)
    {
        var pssError = "The password length should be between 6 to 12 characters"
        res.render("registration", { pssError: pssError, data: registrationData, layout: false});
    }
    else
    {
        res.render("dashboard", {layout: false});
    }

    bcrypt.hash(registrationData.password, 10).then(hash=>{
        let accoutInfo = new user_info({
            firstname: registrationData.firstname,
            lastname: registrationData.lastname,
            username: registrationData.username,
            password: hash,
            address: registrationData.address,
            dob: registrationData.dob,
            phoneD: registrationData.phoneD,
            course: registrationData.course,
            email: registrationData.email
        }).save((e, data) =>{
            if(e)
            {
                console.log(e);
            }
            else
            {
                console.log(data);
            }
        });
    })
    .catch(err=>{
        console.log(err); 
    });
    
});

app.get('/login', function(req, res){
    res.render("login", {layout: false});
});

app.get("/logout", function(req, res) {
    req.session.reset();
    res.redirect("/login");
  });

function specialChar(str)
{
    const speStr = /[`!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?~]/;
    return speStr.test(str);
}

app.post("/login", function(req, res){

    var loginData = {
        usr: req.body.username,
        pss: req.body.password
    }

    if(loginData.usr == "" || loginData.pss == "" )
    {
        var loginError = "The username and the password should be entered!!!";
        res.render("login", { loginError: loginError, data: loginData, layout: false });
    }
    else if(specialChar(loginData.usr) == true) //if there's special character return true
    {
        var specialError = "Special character is not allowed";
        res.render("login", { specialError: specialError, data: loginData, layout: false});
    }
    else
    {
        user_info.findOne({ username: loginData.usr}, ["firstname", "lastname", "username", "password"]).exec().then((data) =>{
            bcrypt.compare(loginData.pss, data.password).then((result) => {
                // result === true
                console.log(result);
                if(result == true) {
                    if(data.id == "638a248edc2696d8b653714a") //admin session
                    {
                        req.session.admData = {
                            username: loginData.usr,
                            password: loginData.pss
                        }
     
                      res.render("adm_dashboard", {firstname:data.firstname, lastname:data.lastname, username:data.username, layout: false});
                      return;
                    }
                    else //user session
                    {
                        req.session.userData = {
                            username: loginData.usr,
                            password: loginData.pss
                        }
                    res.render("login_dashboard", {firstname:data.firstname, lastname:data.lastname, username:data.username, layout: false});
                    return;
                    }
                }
                else
                {
                 var userError = "Sorry, you entered the wrong username and/or password";
                 res.render("login", {userError: userError, data: loginData, layout: false});
                }
            });

         });
        //res.render("dashboard", {layout: false});
    }

});

app.get("/administration", ensureLogin, function(req, res){

    res.render("administration", {layout:false});

});

function ensureLogin(req, res, next) {
    if (!req.session.admData) {
      res.redirect("/login");
    } else {
      next();
    }
  }

app.post("/administration", function(req, res){

    let blogInfo = new blog_content({
        title: req.body.title,
        date : req.body.date,
        content: req.body.content,
        image : req.body.image
    }).save((e, data) =>{
        if(e)
        {
            console.log(e);
        }
        else
        {
            console.log(data);
        }
    });

    res.redirect("/");
});


app.use(function(req,res){
    res.status(404).send("Page not found");
});

var port = process.env.PORT || 8081;
app.listen(port);