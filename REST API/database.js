const mysql = require('mysql2');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'root',
  password: '12345',
  database: 'rastihomma'
});
module.exports = connection;
