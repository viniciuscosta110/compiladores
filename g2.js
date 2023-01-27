
var input = "a^bbb";
var index = 0;
var currentChar = input[index];

function A() {
  if(index === input.length) {
    return;
  }

  if (currentChar === "a") {
    index++;
    currentChar = input[index];
    A();
  } else if (currentChar === "^") {
    index++;
    currentChar = input[index];
    B();
  } else {
    throw `Error: word ${input} is not in the language, currentLine: 16`;
  }
}

function B() {
  if(index === input.length) {
    return;
  }

  if (currentChar === "b") {
    index++;
    currentChar = input[index];
    B();
  } else {
    throw `Error: word ${input} is not in the language, currentLine: 26`;
  }
}

function main() {
  /*
  G2:
    S → AB
    A → aAb
    A → ^
    B → Bb
    B → b
  */
  if(currentChar === "a"){
    index++;
    currentChar = input[index];
    A();
  } else if(currentChar === "^") {
    index++;
    currentChar = input[index];
    B();
  } else {
    throw `Error: word ${input} is not in the language, currentLine: 49`;
  }

  if(index === input.length) {
    console.log("The word is valid!");
  }
}

main();