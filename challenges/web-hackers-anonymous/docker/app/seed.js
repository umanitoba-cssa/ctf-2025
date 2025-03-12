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
    recovery_token VARCHAR(12)
);

CREATE TABLE jobs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    hacker_id BIGINT,
    title TEXT NOT NULL,
    details TEXT NOT NULL,
    contact TEXT NOT NULL,
    date TEXT NOT NULL,
    FOREIGN KEY (hacker_id) REFERENCES users(id)
);

-- Insert 17 users
INSERT INTO users (username, password, recovery_token) VALUES
('shadowhunter', 'password1', 'token1'),
('darkphoenix', 'password2', 'token2'),
('cyberghost', 'password3', 'token3'),
('neonreaper', 'password4', 'token4'),
('voidwalker', 'password5', 'token5'),
('silentkiller', 'password6', 'token6'),
('blackwidow', 'password7', 'token7'),
('phantomhacker', 'password8', 'token8'),
('nightstalker', 'password9', 'token9'),
('crimsonfox', 'password10', 'token10'),
('stealthraider', 'password11', 'token11'),
('shadowblade', 'password12', 'token12'),
('darknetlord', 'password13', 'token13'),
('codebreaker', 'password14', 'token14'),
('zeroday', 'password15', 'token15'),
('hackmaster', 'password16', 'token16'),
('ghostprotocol', 'password17', 'token17');

-- Insert 60 randomized jobs
INSERT INTO jobs (hacker_id, title, details, contact, date) VALUES
(1, 'Silent Infiltration', 'Gain access to a high-security research lab and exfiltrate experimental data.', 'contact1@example.com', '2023-10-01'),
(2, 'Digital Sabotage', 'Disrupt a competitor’s product launch by tampering with their digital infrastructure.', 'contact2@example.com', '2023-10-02'),
(3, 'Ghost in the Network', 'Plant a persistent backdoor in a government agency’s network.', 'contact3@example.com', '2023-10-03'),
(4, 'Social Engineering Mastery', 'Manipulate employees to gain access to a secure facility.', 'contact4@example.com', '2023-10-04'),
(5, 'The Great Heist', 'Steal unreleased software from a tech giant’s internal servers.', 'contact5@example.com', '2023-10-05'),
(6, 'Election Chaos', 'Alter voter registration databases to cause confusion in an upcoming election.', 'contact6@example.com', '2023-10-06'),
(7, 'Data Poisoning', 'Corrupt a machine learning model used by a financial institution.', 'contact7@example.com', '2023-10-07'),
(8, 'Crypto Nightmare', 'Drain funds from a decentralized finance (DeFi) platform.', 'contact8@example.com', '2023-10-08'),
(9, 'Operation Blackout', 'Cause a city-wide power outage by exploiting SCADA systems.', 'contact9@example.com', '2023-10-09'),
(10, 'Phantom Phishing', 'Run a targeted phishing campaign against high-profile executives.', 'contact10@example.com', '2023-10-10'),
(11, 'The Insider', 'Recruit an employee to leak sensitive corporate documents.', 'contact11@example.com', '2023-10-11'),
(12, 'Dark Market Expansion', 'Create a new category for illegal services on a dark web marketplace.', 'contact12@example.com', '2023-10-12'),
(13, 'Botnet Empire', 'Build a massive botnet using compromised IoT devices.', 'contact13@example.com', '2023-10-13'),
(14, 'Zero-Day Auction', 'Sell a zero-day exploit for a widely used operating system.', 'contact14@example.com', '2023-10-14'),
(15, 'Identity Factory', 'Generate fake identities for use in financial fraud schemes.', 'contact15@example.com', '2023-10-15'),
(16, 'Industrial Meltdown', 'Disrupt operations at a chemical plant by tampering with control systems.', 'contact16@example.com', '2023-10-16'),
(17, 'The Silent Witness', 'Delete surveillance footage from a high-security facility.', 'contact17@example.com', '2023-10-17'),
(1, 'Operation Deep Dive', 'Infiltrate a submarine communications network for classified data.', 'contact18@example.com', '2023-10-18'),
(2, 'The Trojan Horse', 'Deliver malware disguised as a software update to a target organization.', 'contact19@example.com', '2023-10-19'),
(3, 'Ghost Protocol', 'Erase all traces of a client’s digital footprint.', 'contact20@example.com', '2023-10-20'),
(4, 'The Puppet Master', 'Take control of a company’s social media accounts to spread disinformation.', 'contact21@example.com', '2023-10-21'),
(5, 'Operation Paper Trail', 'Forge documents to frame a high-profile individual for a crime. cssactf{pR3p@reD-1Nj3c7!0nS-@N0nYm0Us-f9e07432}', 'contact22@example.com', '2023-10-22'),
(6, 'The Invisible Hand', 'Manipulate stock prices by leaking false financial data.', 'contact23@example.com', '2023-10-23'),
(7, 'Operation Smoke Screen', 'Create a diversion by launching a fake cyberattack on a decoy target.', 'contact24@example.com', '2023-10-24'),
(8, 'The Crypto Mirage', 'Create a fake cryptocurrency to scam investors.', 'contact25@example.com', '2023-10-25'),
(9, 'Operation Black Flag', 'Hijack a shipping company’s logistics system to reroute cargo.', 'contact26@example.com', '2023-10-26'),
(10, 'The Phantom Menace', 'Impersonate a high-ranking official to gain access to restricted areas.', 'contact27@example.com', '2023-10-27'),
(11, 'Operation Shadowfall', 'Deploy ransomware on a hospital’s network and demand payment in Monero.', 'contact28@example.com', '2023-10-28'),
(12, 'The Dark Archive', 'Steal and publish confidential documents from a secretive organization.', 'contact29@example.com', '2023-10-29'),
(13, 'Operation Ghost Ship', 'Take control of a cargo ship’s navigation system and reroute it.', 'contact30@example.com', '2023-10-30'),
(14, 'The Silent Storm', 'Disrupt a major sporting event by taking down its live broadcast.', 'contact31@example.com', '2023-10-31'),
(15, 'Operation Black Ice', 'Freeze a bank’s transaction system to cause financial chaos.', 'contact32@example.com', '2023-11-01'),
(16, 'The Phantom Network', 'Create a fake dark web marketplace to trap law enforcement.', 'contact33@example.com', '2023-11-02'),
(17, 'Operation Deep Freeze', 'Lock down a government agency’s systems with ransomware.', 'contact34@example.com', '2023-11-03'),
(1, 'The Ghost Protocol', 'Erase all evidence of a client’s involvement in a cyberattack.', 'contact35@example.com', '2023-11-04'),
(2, 'Operation Dark Horizon', 'Steal blueprints for a next-generation military drone.', 'contact36@example.com', '2023-11-05'),
(3, 'The Silent Breach', 'Infiltrate a nuclear facility’s control systems without detection.', 'contact37@example.com', '2023-11-06'),
(4, 'Operation Phantom Strike', 'Disrupt a global satellite communications network.', 'contact38@example.com', '2023-11-07'),
(5, 'The Black Vault', 'Steal encrypted files from a high-security data center.', 'contact39@example.com', '2023-11-08'),
(6, 'Operation Shadow Veil', 'Create a fake identity to infiltrate a criminal organization.', 'contact40@example.com', '2023-11-09'),
(7, 'The Ghost Network', 'Build a private, untraceable communication network for a client.', 'contact41@example.com', '2023-11-10'),
(8, 'Operation Dark Web', 'Create a fake dark web forum to gather intelligence on rival hackers.', 'contact42@example.com', '2023-11-11'),
(9, 'The Silent Heist', 'Steal rare digital assets from a blockchain-based game.', 'contact43@example.com', '2023-11-12'),
(10, 'Operation Blackout', 'Take down a major news outlet’s website during a critical event.', 'contact44@example.com', '2023-11-13'),
(11, 'The Phantom Heist', 'Steal unreleased music tracks from a famous artist’s private server.', 'contact45@example.com', '2023-11-14'),
(12, 'Operation Ghost Fleet', 'Disrupt a shipping company’s operations by tampering with its fleet tracking system.', 'contact46@example.com', '2023-11-15'),
(13, 'The Dark Mirror', 'Create a fake news website to spread disinformation.', 'contact47@example.com', '2023-11-16'),
(14, 'Operation Silent Storm', 'Deploy malware to disrupt a global financial trading platform.', 'contact48@example.com', '2023-11-17'),
(15, 'The Phantom Code', 'Steal source code for a revolutionary AI algorithm.', 'contact49@example.com', '2023-11-18'),
(16, 'Operation Black Ice', 'Freeze a cryptocurrency exchange’s withdrawal system.', 'contact50@example.com', '2023-11-19'),
(17, 'The Ghost Protocol', 'Erase all traces of a client’s involvement in a data breach.', 'contact51@example.com', '2023-11-20');
INSERT INTO jobs (hacker_id, title, details, contact, date) VALUES
(1, 'Operation Nightfall', 'Infiltrate a military satellite system to intercept classified communications.', 'contact52@example.com', '2023-11-21'),
(2, 'The Shadow Broker', 'Sell stolen intelligence data to the highest bidder on the dark web.', 'contact53@example.com', '2023-11-22'),
(3, 'Operation Phantom Key', 'Steal encryption keys from a secure messaging app used by government officials.', 'contact54@example.com', '2023-11-23'),
(4, 'The Silent Auction', 'Hack into an online auction platform to manipulate bidding on high-value items.', 'contact55@example.com', '2023-11-24'),
(5, 'Operation Dark Harvest', 'Steal agricultural data from a biotech firm to sabotage their research.', 'contact56@example.com', '2023-11-25'),
(6, 'The Ghost Protocol', 'Erase all evidence of a client’s involvement in a high-profile data breach.', 'contact57@example.com', '2023-11-26'),
(7, 'Operation Blackout', 'Disrupt a major city’s traffic control systems to cause chaos.', 'contact58@example.com', '2023-11-27'),
(8, 'The Phantom Heist', 'Steal rare digital art from a blockchain-based NFT platform.', 'contact59@example.com', '2023-11-28'),
(9, 'Operation Silent Storm', 'Deploy malware to disrupt a global financial trading platform.', 'contact60@example.com', '2023-11-29'),
(10, 'The Dark Mirror', 'Create a fake news website to spread disinformation about a political candidate.', 'contact61@example.com', '2023-11-30'),
(11, 'Operation Ghost Fleet', 'Disrupt a shipping company’s operations by tampering with its fleet tracking system.', 'contact62@example.com', '2023-12-01'),
(12, 'The Silent Witness', 'Delete surveillance footage from a high-security facility.', 'contact63@example.com', '2023-12-02'),
(13, 'Operation Deep Dive', 'Infiltrate a submarine communications network for classified data.', 'contact64@example.com', '2023-12-03'),
(14, 'The Trojan Horse', 'Deliver malware disguised as a software update to a target organization.', 'contact65@example.com', '2023-12-04'),
(15, 'Operation Picture Frame', 'Deepfake photos to frame an oligarch for a crime.', 'contact66@example.com', '2023-12-05'),
(16, 'The Invisible Hand', 'Manipulate stock prices by leaking false financial data.', 'contact67@example.com', '2023-12-06'),
(17, 'Operation Smoke Screen', 'Create a diversion by launching a fake cyberattack on a decoy target.', 'contact68@example.com', '2023-12-07'),
(1, 'The Crypto Mirage', 'Create a fake cryptocurrency to scam investors.', 'contact69@example.com', '2023-12-08'),
(2, 'Operation Black Flag', 'Hijack a shipping company’s logistics system to reroute cargo.', 'contact70@example.com', '2023-12-09'),
(3, 'The Phantom Menace', 'Impersonate a high-ranking official to gain access to restricted areas.', 'contact71@example.com', '2023-12-10'),
(4, 'Operation Shadowfall', 'Deploy ransomware on a hospital’s network and demand payment in Monero.', 'contact72@example.com', '2023-12-11'),
(5, 'The Dark Archive', 'Steal and publish confidential documents from a secretive organization.', 'contact73@example.com', '2023-12-12'),
(6, 'Operation Ghost Ship', 'Take control of a cargo ship’s navigation system and reroute it.', 'contact74@example.com', '2023-12-13'),
(7, 'The Silent Storm', 'Disrupt a major sporting event by taking down its live broadcast.', 'contact75@example.com', '2023-12-14'),
(8, 'Operation Black Ice', 'Freeze a bank’s transaction system to cause financial chaos.', 'contact76@example.com', '2023-12-15'),
(9, 'The Phantom Network', 'Create a fake dark web marketplace to trap law enforcement.', 'contact77@example.com', '2023-12-16'),
(10, 'Operation Deep Freeze', 'Lock down a government agency’s systems with ransomware.', 'contact78@example.com', '2023-12-17'),
(11, 'The Ghost Protocol', 'Erase all evidence of a client’s involvement in a cyberattack.', 'contact79@example.com', '2023-12-18'),
(12, 'Operation Dark Horizon', 'Steal blueprints for a next-generation military drone.', 'contact80@example.com', '2023-12-19'),
(13, 'The Silent Breach', 'Infiltrate a nuclear facility’s control systems without detection.', 'contact81@example.com', '2023-12-20'),
(14, 'Operation Phantom Strike', 'Disrupt a global satellite communications network.', 'contact82@example.com', '2023-12-21'),
(15, 'The Black Vault', 'Steal encrypted files from a high-security data center.', 'contact83@example.com', '2023-12-22'),
(16, 'Operation Shadow Veil', 'Create a fake identity to infiltrate a criminal organization.', 'contact84@example.com', '2023-12-23'),
(17, 'The Ghost Network', 'Build a private, untraceable communication network for a client.', 'contact85@example.com', '2023-12-24'),
(1, 'Operation Dark Web', 'Create a fake dark web forum to gather intelligence on rival hackers.', 'contact86@example.com', '2023-12-25'),
(2, 'The Silent Heist', 'Steal rare digital assets from a blockchain-based game.', 'contact87@example.com', '2023-12-26'),
(3, 'Operation Blackout', 'Take down a major news outlet’s website during a critical event.', 'contact88@example.com', '2023-12-27'),
(4, 'The Phantom Heist', 'Steal unreleased music tracks from a famous artist’s private server.', 'contact89@example.com', '2023-12-28'),
(5, 'Operation Ghost Fleet', 'Disrupt a shipping company’s operations by tampering with its fleet tracking system.', 'contact90@example.com', '2023-12-29'),
(6, 'The Dark Mirror', 'Create a fake news website to spread disinformation.', 'contact91@example.com', '2023-12-30'),
(7, 'Operation Silent Storm', 'Deploy malware to disrupt a global financial trading platform.', 'contact92@example.com', '2023-12-31'),
(8, 'The Phantom Code', 'Steal source code for a revolutionary AI algorithm.', 'contact93@example.com', '2024-01-01'),
(9, 'Operation Black Ice', 'Freeze a cryptocurrency exchange’s withdrawal system.', 'contact94@example.com', '2024-01-02'),
(10, 'The Ghost Protocol', 'Erase all traces of a client’s involvement in a data breach.', 'contact95@example.com', '2024-01-03'),
(11, 'Operation Nightfall', 'Infiltrate a military satellite system to intercept classified communications.', 'contact96@example.com', '2024-01-04'),
(12, 'The Shadow Broker', 'Sell stolen intelligence data to the highest bidder on the dark web.', 'contact97@example.com', '2024-01-05'),
(13, 'Operation Phantom Key', 'Steal encryption keys from a secure messaging app used by government officials.', 'contact98@example.com', '2024-01-06'),
(14, 'The Silent Auction', 'Hack into an online auction platform to manipulate bidding on high-value items.', 'contact99@example.com', '2024-01-07'),
(15, 'Operation Dark Harvest', 'Steal agricultural data from a biotech firm to sabotage their research.', 'contact100@example.com', '2024-01-08'),
(16, 'The Ghost Protocol', 'Erase all evidence of a client’s involvement in a high-profile data breach.', 'contact101@example.com', '2024-01-09'),
(17, 'Operation Blackout', 'Disrupt a major city’s traffic control systems to cause chaos.', 'contact102@example.com', '2024-01-10');
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
    let recovery_token = randomString(12, 12)

    // update the password in the database
    db.prepare('UPDATE users SET password = ? WHERE id = ?;').run(hash, i + 1)
    console.log(`Updated password for user ${i + 1} to ${password}`)

    // update the recovery token in the database
    db.prepare('UPDATE users SET recovery_token = ? WHERE id = ?;').run(recovery_token, i + 1)
    console.log(`Updated recovery token for user ${i + 1} to ${recovery_token}`)
}

let numJobs = db.prepare('SELECT COUNT(*) FROM jobs;').get()['COUNT(*)']

// update contact field to random onion emails
console.log("Updating job contact fields")
for (let i = 0; i < numJobs; i++) {
    let alias = randomString(10, 20)
    let domain = randomString(56, 56) + '.onion'
    let email = `${alias}@${domain}`
    db.prepare('UPDATE jobs SET contact = ? WHERE id = ?;').run(email, i + 1)
}

let users_table = db.prepare('SELECT * FROM users;').all()
console.log(users_table)