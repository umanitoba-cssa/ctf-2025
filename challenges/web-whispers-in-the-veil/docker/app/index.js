import express, { application } from 'express';
import Database from 'libsql';
import bodyparser from 'body-parser'
import cookieParser from 'cookie-parser'
import 'dotenv/config'

// express setup
const port = process.env.PORT
const app = express()

// sqlite setup
const db = new Database('./database.sqlite')

app.use(bodyparser.urlencoded({ extended: false }))
app.use(cookieParser())
app.use(express.static('public'))

function get_valid_attributes(table) {
    return db.prepare(`select name from pragma_table_info('${table}');`).all().map((x) => x.name)
}

app.get('/api/currentuser', (req, res) => {
    let token = req.cookies.session

    if (!token) {
        res.status(401).send('Unauthorized')
        return
    }

    try {
        let user = db.prepare('SELECT username FROM users WHERE session_token = ?').get(token)

        if (!user) {
            res.status(401).send('Unauthorized')
            return
        }

        res.send(user.username);
    } catch (e) {
        res.status(401).send('Unauthorized')
    }
});

// Writing this for the team section, but I think we will need to display
// users in a few places, so I made this method pretty flexible.
app.get('/api/users', (req, res) => {

    /** @type {Object.<string, string>} */
    let q = req.query;
    
    try {
        let {include, ...filters} = q;
        include = include ? include.split(',') : null

        if (Object.keys(filters).length === 0) {
            res.status(400).send("Please provide at least one attribute to filter on");
            return;
        }

        let select = [];
        let filter = [];
        let params = [];

        let valid_attributes = get_valid_attributes('users');

        for (let key of include) {
            if (valid_attributes.includes(key)) {
                select.push(key);
            }
        }

        for (let key in filters) {
            if (valid_attributes.includes(key)) {
                filter.push(`${key} = ?`);
                params.push(filters[key]);
            }
        }

        let query = `SELECT ${select.join(', ')} FROM users WHERE ${filter.join(' AND ')};`;
        let users = db.prepare(query).all(...params);

        res.send(users);
    } catch (e) {
        res.status(500).send("Internal Server Error")
    }
});

app.get('/api/conversations', (req, res) => {
    let token = req.cookies.session

    if (!token) {
        res.status(401).send('Unauthorized')
        return
    }

    try {
        let user = db.prepare('SELECT id FROM users WHERE session_token = ?').get(token)

        if (!user) {
            res.status(401).send('Unauthorized')
            return
        }

        let conversations = db.prepare(
            `
            SELECT 
                conversations.id as id, other_user.username AS other_user
            FROM 
                conversations 
            JOIN
                users other_user
            ON
                conversations.sender_user_id = other_user.id
            WHERE 
                conversations.recipient_user_id = ?
            UNION
            SELECT 
                conversations.id as id, other_user.username AS other_user
            FROM 
                conversations 
            JOIN
                users other_user
            ON
                conversations.recipient_user_id = other_user.id
            WHERE 
                conversations.sender_user_id = ?
            ;`
        ).all(user.id, user.id);


        res.send(conversations);
    } catch (e) {
        res.status(401).send('Unauthorized')
    }
});

app.get('/api/conversations/:conversationId', (req, res) => {
    let conversationId = req.params.conversationId
    let token = req.cookies.session

    if (!token || !conversationId) {
        res.status(401).send('Unauthorized')
        return
    }

    try {
        let user = db.prepare('SELECT id FROM users WHERE session_token = ?').get(token)

        if (!user) {
            res.status(401).send('Unauthorized')
            return
        }

        let conversation = db.prepare(
            `
            SELECT 
                messages.id as id, (sender.id == ?) as is_self, sender.username as sender, content, timestamp
            FROM 
                messages 
            INNER JOIN
                conversations
            ON
                conversations.id = messages.conversation_id
            INNER JOIN
                users as sender
            ON
                sender.id = messages.sender_id
            WHERE
                conversations.id = ?
                AND
                (
                    conversations.sender_user_id = ?
                    OR
                    conversations.recipient_user_id = ?
                )
            ;`
        ).all(user.id, conversationId, user.id, user.id);

        if (!conversation) {
            res.status(401).send('Unauthorized')
            return
        }

        res.send(conversation);
    } catch (e) {
        res.status(401).send('Unauthorized')
    }
});

function randomString(minlength, maxlength) {
    let length = Math.floor(Math.random() * (maxlength - minlength + 1)) + minlength
    let result = ''
    let characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'

    for (let i = 0; i < length; i++) {
        result += characters.charAt(Math.floor(Math.random() * characters.length))
    }

    return result
}

function prepareSessionToken(username) {
    let session_token = randomString(128, 128)
    db.prepare('UPDATE users SET session_token = ? WHERE username = ?;').run(session_token, username)
    return session_token
}

app.post('/api/login', (req, res) => {
    let { username, password, action } = req.body

    if (process.env.MAINTENANCE_MODE === 'true') {
        res.cookie('error', 'The system is currently in maintenance mode. Please try again later.')
        res.redirect(req.get("Referrer") || "/")
        return
    }

    try {
        let user = db.prepare(`SELECT username, password FROM users WHERE username = ?;`).get(username)

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

        let token = prepareSessionToken(user.username)
        res.cookie('session', token)
        res.redirect('/chat.html')
    } catch (e) {
        res.cookie('error', 'Invalid username or password')
        res.redirect(req.get("Referrer") || "/")
        return
    }
});

app.get('/api/logout', (req, res) => {
    res.cookie('session', '', { expires: new Date(0), 'path': '/' })
    res.redirect('/')
});

app.listen(port, () => {
    console.log(`App listening on port ${port}`)
})
