import express from 'express';
import { promisify } from 'util';
import { exec as execSync } from 'child_process';
import fs from 'fs/promises'
import path from 'path';
import 'dotenv/config'

// express setup
const port = process.env.PORT
const app = express()

function makePage(directory, fileList) {
    let previousPath = path.normalize(path.join(directory, '..'));
    let goback = '';
    if (directory !== '/') {
        goback = `<li><a href="${previousPath}">..</a></li>`;
    }

    return `
        <html>
        <head>
            <title>File Server</title>
        </head>
        <body>
            <h1>Files</h1>
            <p>Current path: ${directory}</p>
            <ul>
                ${goback}
                ${fileList.map(file => `<li><a href="${encodeURIComponent(path.join(directory, file))}">${file}</a></li>`).join('')}
            </ul>
        </body>
    </html>
    `;
}

app.get('*', async (req, res) => {
    let directory = decodeURIComponent(req.url);
    let realpath = path.join(process.env.BASE_PATH, directory);
    realpath = path.normalize(realpath);
    realpath = path.resolve(realpath);

    try {
        const isFile = (await fs.stat(realpath)).isFile();

        if (isFile) {
            res.sendFile(realpath);
            return;
        }

        const list = await fs.readdir(realpath);

        res.send(makePage(directory, list));
    } catch (e) {
        res.status(404).send('Not found');
    }
});

app.listen(port, () => {
    console.log(`App listening on port ${port}`)
})
