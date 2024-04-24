const mysql = require('mysql2');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'root',
  password: 'kanakana1',
  database: 'rastihomma'
});
module.exports = connection;