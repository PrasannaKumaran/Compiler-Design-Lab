const express = require("express");
const asyncHandler = require('express-async-handler');
require("dotenv").config();
const permissions = require("./permissions_base")

const app = express();
const PORT = process.env.PORT; 

app.use(express.json());

app.get("/", function(req,res){
     res.send("<h1>This is the documentation page</h1>");
});

app.post("/", function(req, res){
    res.send(req.body);
});

app.post("/permission", asyncHandler(async (req, res) => {
    try {
        const caller_token = req.body.authentication_token;
        const query = req.body.data;
        res.json(await permissions(caller_token, query));
    } catch(error) {
        res.status(400).json({"message" : `Error fetching permissions. ${error}`});
    }
}));

app.post("/force",function(req, res){
    res.send(req.body);
    console.log(req.body);
});

app.listen(PORT, function(error){
    if(error){
        console.log(`Something went wrong ${error}`);
    } else{
        console.log(`Server is listening on port ${PORT}`);
    }
});

