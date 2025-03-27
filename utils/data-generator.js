const fs = require('fs');
const path = require('path');

const DEPARTMENTS = ['HR', 'Engineering', 'Finance', 'Marketing', 'Sales', 'IT', 'Customer Support', 'Legal', 'Operations', 'Research'];

function generateRandomString(length) {
  return (Math.random() + 1).toString(36).substring(7);
}

// Generate random employee data
function generateData(id) {
  const firstname = generateRandomString(6); // generate 6 random letters
  const lastname = generateRandomString(8); // generate 8 random letters
  const name = `${firstname} ${lastname}`;
  const department = DEPARTMENTS[Math.floor(Math.random() * DEPARTMENTS.length)];
  const salary = Math.floor(Math.random() * 1000000) + 30000; // Random salary between 30,000 and 1,300,000
  
  return {
    name,
    id,
    department,
    salary
  };
}

function main(outputPath, amount = 100) {
  const data = {
    employees: []
  };
  
  for (let i = 1; i <= amount; i++) {
    data.employees.push(generateData(i));
  }
  
  const outputDir = path.dirname(outputPath);
  if (!fs.existsSync(outputDir)) {
    fs.mkdirSync(outputDir, { recursive: true });
  }
  
  // Write data to file
  fs.writeFileSync(outputPath, JSON.stringify(data, null, 2));
  console.log(`Generated ${amount} employee records and saved to ${outputPath}`);
}

console.log(process.argv.toString());
const args = process.argv.slice(2);
if (args.length === 0) {
  console.error('Usage: node data-generator.js <output-path> [amount]');
  process.exit(1);
}

const outputPath = args[0];
const amount = args.length > 1 ? parseInt(args[1], 10) : 100;

if (isNaN(amount)) {
  console.error('Amount must be a number');
  process.exit(1);
}

main(outputPath, amount);
