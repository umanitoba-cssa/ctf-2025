import express, { application } from 'express';
import bcrypt from 'bcrypt';
import Database from 'libsql';
import bodyparser from 'body-parser'
import cookieParser from 'cookie-parser'
import jsonwebtoken from 'jsonwebtoken';
const { sign, decode, verify } = jsonwebtoken;
import 'dotenv/config'

// express setup
const port = process.env.PORT
const app = express()

// sqlite setup
const db = new Database('./database.sqlite')

// util funcs
function getAuthJwt(username) {
    return sign({ id: username }, process.env.JWT_SECRET)
}

app.use(bodyparser.urlencoded({ extended: false }))
app.use(cookieParser())
app.use(express.static('public'))

app.post('/api/auth/login', (req, res) => {
    let { id, password, action } = req.body

    try {
        let user = db.prepare(`SELECT username, password FROM users WHERE id = ?;`).get(id)

        if (!user) {
            res.cookie('error', 'Invalid username or password')
            res.redirect(req.get("Referrer") || "/")
            return
        }

        if (!bcrypt.compareSync(password, user.password)) {
            res.cookie('error', `Invalid password for user`)
            res.redirect(req.get("Referrer") || "/")
            return
        }

        let session = getAuthJwt(id)
        res.cookie('session', session)
        res.redirect('/dashboard.html?result=success')
    } catch (e) {
        res.cookie('error', 'Invalid username or password')
        res.redirect(req.get("Referrer") || "/")
        return
    }
});

app.get('/api/checkuser', (req, res) => {
    let token = req.cookies.auth

    if (!token) {
        res.status(401).send('Unauthorized')
        return
    }

    try {
        let decoded = verify(token, process.env.JWT_SECRET)
        res.send(decoded.id)
    } catch (e) {
        res.status(401).send('Unauthorized')
    }
});

app.get('/api/jobs', (req, res) => {
    let token = req.cookies.auth

    if (!token) {
        res.status(401).send('Unauthorized')
        return
    }

    try {
        let decoded = verify(token, process.env.JWT_SECRET)
        let hacker_id = db.prepare(`SELECT id FROM users WHERE username = ?;`).get(decoded.id).id
        let jobs = db.prepare(`SELECT * FROM jobs WHERE jobs.hacker_id = ?;`).all(hacker_id, hacker_id);

        res.send(jobs);
    } catch (e) {
        res.status(401).send('Unauthorized')
    }
});

app.get('/api/logout', (req, res) => {
    res.clearCookie('auth')
    res.redirect('/')
});

app.listen(port, () => {
    console.log(`App listening on port ${port}`)
})
