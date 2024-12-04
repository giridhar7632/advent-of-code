const fs = require('fs')

const left = []
const right = [];

fs.readFileSync('./ip.txt', 'utf8').split('\n').map(s => {
    const [l, r] = s.split('  ')
    left.push(parseInt(l.trim()))
    right.push(parseInt(r.trim()))
})

const sortedLeft = left.sort((a, b) => b - a)
const sortedRight = right.sort((a, b) => b - a)

let sum = 0;

for(let i = 0; i < sortedLeft.length; i++) {
    sum += Math.abs(sortedLeft[i] - sortedRight[i])
}

console.log('sum: ', sum)

const countMap = {}
for(const i of sortedRight) {
    countMap[i] = countMap[i] ? countMap[i] + 1 : 1
}

let similarityScore = 0;

for(const i of sortedLeft) {
    if(countMap[i]) {
        similarityScore += (i * countMap[i]);
    }
}

console.log('similarityScore: ', similarityScore)