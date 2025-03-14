import bcrypt from 'bcrypt';
import Database from 'libsql';
import fs from 'fs';

// bcrypt setup
const saltRounds = 10;

// sqlite setup
fs.unlinkSync('./database.sqlite')
const db = new Database('./database.sqlite')

let init_query = `
-- Create tables
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL,
    password TEXT NOT NULL,
    session_token TEXT,
    is_team BOOLEAN NOT NULL DEFAULT 0,
    title TEXT,
    bio TEXT
);

CREATE TABLE conversations (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    sender_user_id INTEGER NOT NULL,
    recipient_user_id INTEGER NOT NULL,
    FOREIGN KEY (sender_user_id) REFERENCES users(id),
    FOREIGN KEY (recipient_user_id) REFERENCES users(id)
);

CREATE TABLE messages (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    conversation_id INTEGER NOT NULL,
    sender_id INTEGER NOT NULL,
    content TEXT NOT NULL,
    timestamp TEXT NOT NULL,
    FOREIGN KEY (conversation_id) REFERENCES conversations(id),
    FOREIGN KEY (sender_id) REFERENCES users(id)
);

-- Seed users
INSERT INTO users (username, password, session_token) VALUES
('PhantomPhreak', 'placeholder_password', 'placeholder_token'),
('DarkDante', 'placeholder_password', 'placeholder_token'),
('ZeroCool', 'placeholder_password', 'placeholder_token'),
('AcidBurn', 'placeholder_password', 'placeholder_token'),
('nexxode', 'placeholder_password', 'placeholder_token')
;

-- Team members
INSERT INTO users (username, password, session_token, is_team, title, bio) VALUES
('toxicleopard', 'placeholder_password', 'placeholder_token', 1, 'Founder & CEO', 'Former cybersecurity expert with 15+ years of experience in security technologies.'),
('iWireless', 'placeholder_password', 'placeholder_token', 1, 'CTO', 'Cryptography sepcialist with a background in developing secure communication systems.'),
('SmartAlex', 'placeholder_password', 'placeholder_token', 1, 'Head of Security', 'Ethical hacker and security researcher forcused on patching vulnerabilities.'),
('cr0sspizza', 'placeholder_password', 'placeholder_token', 1, 'Privacy Officer', 'Legal expert specializing in digital privacy laws and data protection regulations.')
;

-- Seed conversations
INSERT INTO conversations (sender_user_id, recipient_user_id) VALUES
-- PhantomPhreak's conversations
(1, 2), (1, 3),
-- DarkDante's conversations
(2, 3), (2, 4),
-- ZeroCool's conversations
(3, 4), (3, 5),
-- AcidBurn's conversations
(4, 5),
-- nexxode's conversations
(5, 1), (5, 3);

-- Conversation 10: PhantomPhreak -> AcidBurn
INSERT INTO conversations (sender_user_id, recipient_user_id) VALUES
(1, 4);

-- Conversation 11: DarkDante -> nexxode
INSERT INTO conversations (sender_user_id, recipient_user_id) VALUES
(2, 5);

-- Conversation 12: ZeroCool -> DarkDante
INSERT INTO conversations (sender_user_id, recipient_user_id) VALUES
(3, 2);

-- Conversation 13: AcidBurn -> PhantomPhreak
INSERT INTO conversations (sender_user_id, recipient_user_id) VALUES
(4, 1);

-- Conversation 14: nexxode -> AcidBurn
INSERT INTO conversations (sender_user_id, recipient_user_id) VALUES
(5, 4);

-- Seed messages
-- Conversation 1: PhantomPhreak -> DarkDante
INSERT INTO messages (conversation_id, sender_id, content, timestamp) VALUES
(1, 1, 'Hey, did you get the payload working?', '2023-10-01T12:34:56Z'),
(1, 2, 'Almost, just need to bypass the firewall.', '2023-10-01T12:35:10Z'),
(1, 1, 'Let me know if you need help with the exploit.', '2023-10-01T12:36:22Z');

-- Conversation 2: PhantomPhreak -> ZeroCool
INSERT INTO messages (conversation_id, sender_id, content, timestamp) VALUES
(2, 1, 'We need to coordinate the DDoS attack.', '2023-10-02T09:12:45Z'),
(2, 3, 'I’m ready. Just give me the target IP.', '2023-10-02T09:13:20Z'),
(2, 1, '192.168.1.100. Launch at 10:00 sharp.', '2023-10-02T09:14:00Z'),
(2, 3, 'Understood.', '2023-10-02T09:14:30Z');

-- Conversation 3: DarkDante -> ZeroCool
INSERT INTO messages (conversation_id, sender_id, content, timestamp) VALUES
(3, 2, 'Did you crack the admin password yet?', '2023-10-03T15:22:11Z'),
(3, 3, 'Not yet, but I’m close. The hash is tough.', '2023-10-03T15:23:00Z'),
(3, 2, 'Hurry up, we need access ASAP.', '2023-10-03T15:24:15Z');

-- Conversation 4: DarkDante -> AcidBurn
INSERT INTO messages (conversation_id, sender_id, content, timestamp) VALUES
(4, 2, 'The data breach is complete. What’s next?', '2023-10-04T18:45:30Z'),
(4, 4, 'Exfiltrate the data and cover our tracks.', '2023-10-04T18:46:10Z'),
(4, 2, 'Got it. I’ll start the transfer.', '2023-10-04T18:47:00Z');

-- Conversation 5: ZeroCool -> AcidBurn
INSERT INTO messages (conversation_id, sender_id, content, timestamp) VALUES
(5, 3, 'I found a vulnerability in their API.', '2023-10-05T11:11:11Z'),
(5, 4, 'Nice! Can we escalate privileges?', '2023-10-05T11:12:00Z'),
(5, 3, 'Yes, but we need to move fast before they patch it.', '2023-10-05T11:13:20Z');

-- Conversation 6: ZeroCool -> nexxode
INSERT INTO messages (conversation_id, sender_id, content, timestamp) VALUES
(6, 3, 'The botnet is ready. Let’s deploy it.', '2023-10-06T14:30:00Z'),
(6, 5, 'Roger that. Sending the command now.', '2023-10-06T14:31:15Z'),
(6, 3, 'Make sure to anonymize the traffic.', '2023-10-06T14:32:00Z'),
(6, 5, 'Already on it.', '2023-10-06T14:32:45Z');

-- Conversation 7: AcidBurn -> nexxode
INSERT INTO messages (conversation_id, sender_id, content, timestamp) VALUES
(7, 4, 'The ransomware is deployed. Waiting for payment.', '2023-10-07T20:00:00Z'),
(7, 5, 'Good. Let’s hope they pay up quickly.', '2023-10-07T20:01:10Z'),
(7, 4, 'If not, we’ll escalate.', '2023-10-07T20:02:00Z');

-- Conversation 8: nexxode -> PhantomPhreak
INSERT INTO messages (conversation_id, sender_id, content, timestamp) VALUES
(8, 5, 'We need to discuss the next target.', '2023-10-08T10:15:30Z'),
(8, 1, 'I’ve got a list ready. Let’s meet at the usual place.', '2023-10-08T10:16:20Z'),
(8, 5, 'Understood. See you there.', '2023-10-08T10:17:00Z'),
(8, 5, 'By the way, heres your payment for the last one.', '2023-10-08T10:18:00Z'),
(8, 5, 'cssactf{@rb1Tr4rY-atTr!bUt3$-a11oW-aUt#3n7Ic@ti0N-732a1d35}', '2023-10-08T10:18:05Z'),
(8, 1, 'Sweet, thx', '2023-10-08T10:18:05Z');

-- Conversation 9: nexxode -> ZeroCool
INSERT INTO messages (conversation_id, sender_id, content, timestamp) VALUES
(9, 5, 'The exploit kit is updated. Ready for distribution.', '2023-10-09T16:45:00Z'),
(9, 3, 'Perfect. Let’s push it to the network.', '2023-10-09T16:46:10Z'),
(9, 5, 'Already on it. Targets are loading.', '2023-10-09T16:47:00Z');

-- Conversation 10: PhantomPhreak -> AcidBurn
INSERT INTO messages (conversation_id, sender_id, content, timestamp) VALUES
(10, 1, 'I need your help with a SQL injection exploit.', '2023-10-10T08:20:00Z'),
(10, 4, 'What’s the target?', '2023-10-10T08:21:15Z'),
(10, 1, 'A financial institution. Their filters are weak.', '2023-10-10T08:22:30Z'),
(10, 4, 'Send me the details. I’ll take a look.', '2023-10-10T08:23:45Z');

-- Conversation 11: DarkDante -> nexxode
INSERT INTO messages (conversation_id, sender_id, content, timestamp) VALUES
(11, 2, 'The payload is ready. Are the bots online?', '2023-10-11T13:45:00Z'),
(11, 5, 'Yes, all systems are go.', '2023-10-11T13:46:10Z'),
(11, 2, 'Good. Launch the attack at 14:00.', '2023-10-11T13:47:20Z'),
(11, 5, 'Understood. Initiating sequence.', '2023-10-11T13:48:00Z');

-- Conversation 12: ZeroCool -> DarkDante
INSERT INTO messages (conversation_id, sender_id, content, timestamp) VALUES
(12, 3, 'I found a zero-day in their system.', '2023-10-12T17:30:00Z'),
(12, 2, 'How severe is it?', '2023-10-12T17:31:15Z'),
(12, 3, 'Critical. We can get root access.', '2023-10-12T17:32:30Z'),
(12, 2, 'Exploit it before they patch it.', '2023-10-12T17:33:45Z'),
(12, 3, 'Already working on it.', '2023-10-12T17:34:00Z');

-- Conversation 13: AcidBurn -> PhantomPhreak
INSERT INTO messages (conversation_id, sender_id, content, timestamp) VALUES
(13, 4, 'The data is encrypted. What’s the decryption key?', '2023-10-13T09:10:00Z'),
(13, 1, 'Check your secure drop. I sent it there.', '2023-10-13T09:11:15Z'),
(13, 4, 'Got it. Decrypting now.', '2023-10-13T09:12:30Z'),
(13, 1, 'Let me know if you hit any snags.', '2023-10-13T09:13:45Z');

-- Conversation 14: nexxode -> AcidBurn
INSERT INTO messages (conversation_id, sender_id, content, timestamp) VALUES
(14, 5, 'The ransomware payment came through.', '2023-10-14T22:00:00Z'),
(14, 4, 'Good. Transfer the funds to the offshore account.', '2023-10-14T22:01:15Z'),
(14, 5, 'Already done. What’s next?', '2023-10-14T22:02:30Z'),
(14, 4, 'We move on to the next target.', '2023-10-14T22:03:45Z');
`

db.exec(init_query)

function randomString(minlength, maxlength) {
    let length = Math.floor(Math.random() * (maxlength - minlength + 1)) + minlength
    let result = ''
    let characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'

    for (let i = 0; i < length; i++) {
        result += characters.charAt(Math.floor(Math.random() * characters.length))
    }

    return result
}

let numUsers = db.prepare('SELECT COUNT(*) FROM users;').get()['COUNT(*)']

for (let i = 0; i < numUsers; i++) {
    // generate a random string between 10 and 32 characters
    let password = randomString(10, 32)
    let hash = bcrypt.hashSync(password, saltRounds)
    let session_token = randomString(128, 128)

    // update the password in the database
    db.prepare('UPDATE users SET password = ? WHERE id = ?;').run(hash, i + 1)
    console.log(`Updated password for user ${i + 1} to ${password}`)

    // update the recovery token in the database
    db.prepare('UPDATE users SET session_token = ? WHERE id = ?;').run(session_token, i + 1)
    console.log(`Updated session token for user ${i + 1}`)
}

let users_table = db.prepare('SELECT * FROM users;').all()
console.log(users_table)