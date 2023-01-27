var input = "baaaaa";
var index = 0;
var currentChar = input[index];

function S() {
	if (currentChar === "b") {
		index++;
		currentChar = input[index];
		B(input);
	} else {
		throw `Error: word ${input} is not in the language`;
	}
}

function B() {
	if (currentChar === "a") {
		index++;
		currentChar = input[index];
		if (currentChar === "a") {
			index++;
			currentChar = input[index];
			B();
		}
	} else {
		throw `Error: word ${input} is not in the language`;
	}
}

function main() {
	/* 
	G1:
		S → bB 
		B → Baa
		B → a 
        
	*/
	S();

	console.log("The word is in the language");
}

main();