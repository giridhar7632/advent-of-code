const fs = require('fs')

const allReports = []

fs.readFileSync('ip.txt', 'utf8')
    .split('\n')
    .map(report => allReports.push(report.trim().split(' ')))

    console.log('all reports', allReports.length)

// a report only counts as safe if both of the following are true:
// 1. The levels are either all increasing or all decreasing.
// 2. Any two adjacent levels differ by at least one and at most three.
function isSafe(report) {
    if (report.length <= 1) return true;
    
    let isIncreasing = true;
    let isDecreasing = true;
    
    for (let i = 1; i < report.length; i++) {
        const diff = report[i] - report[i - 1];
        
        if (Math.abs(diff) < 1 || Math.abs(diff) > 3) {
            return false;
        }
        
        if (diff < 0) {
            isIncreasing = false;
        } else if (diff > 0) {
            isDecreasing = false;
        }
        
        if (!isIncreasing && !isDecreasing) {
            return false;
        }
    }
    
    return true;
}

function canBeSafe(report) {
    // check if the array can be safe after removing one element
    for (let i = 0; i < report.length; i++) {
        let newReport = report.slice(0, i).concat(report.slice(i + 1))
        if (isSafe(newReport)) {
            return true
        }
    }
    return false
}

let cnt = 0
for (let i = 0; i < allReports.length; i++) {
    if (isSafe(allReports[i])) {
        cnt += 1
    } else if (canBeSafe(allReports[i])) {
        cnt += 1
    }
}

console.log('cnt', cnt)