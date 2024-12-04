const fs = require('fs');

const input = fs.readFileSync('ip.txt', 'utf-8');

function findValidMultiplications() {
    let totalSum = 0;
    const mulRegex = /mul\((\d+),\s*(\d+)\)|do\(\)|don't\(\)/g;
    let disabled = false;
    
    // Process each mul instruction
    let match;
    while ((match = mulRegex.exec(input)) !== null) {
        if (match[0] === "don't()") {
            disabled = true;
        } else if (match[0] === "do()") {
            disabled = false;
        } else if (!disabled) {
            const num1 = parseInt(match[1]);
            const num2 = parseInt(match[2]);
            totalSum += num1 * num2;
        }
    }
    
    return totalSum;
}

console.log(findValidMultiplications());