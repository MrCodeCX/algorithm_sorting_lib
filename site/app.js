const algorithmSelect = document.getElementById("algorithm");
const valuesInput = document.getElementById("values");
const runButton = document.getElementById("run");
const shuffleButton = document.getElementById("shuffle");
const speedInput = document.getElementById("speed");
const barsElement = document.getElementById("bars");
const statusElement = document.getElementById("status");
const activeAlgorithmElement = document.getElementById("activeAlgorithm");
const progressCurrentElement = document.getElementById("progressCurrent");
const progressTotalElement = document.getElementById("progressTotal");
const comparisonsElement = document.getElementById("comparisons");
const swapsElement = document.getElementById("swaps");
const writesElement = document.getElementById("writes");
const finalSizeElement = document.getElementById("finalSize");
const eventOutput = document.getElementById("eventOutput");

let sortingModulePromise = null;
let currentResult = null;
let currentStep = 0;
let animationTimer = null;
let isLoading = false;

function getSortingModule() {
	if (!sortingModulePromise) {
		sortingModulePromise = createSortingModule();
	}
	return sortingModulePromise;
}

function parseValues(raw) {
	const values = raw
		.split(/[\s,;]+/)
		.map((value) => Number.parseInt(value.trim(), 10))
		.filter((value) => Number.isFinite(value))
		.slice(0, 32)
		.map((value) => Math.max(-99, Math.min(99, value)));

	return values.length > 0 ? values : [9, 4, 7, 1, 6, 2];
}

function buildRandomValues() {
	const size = 16;
	const values = [];
	for (let i = 0; i < size; i += 1) {
		values.push(Math.floor(Math.random() * 90) + 5);
	}
	return values;
}

async function runSort() {
	stopAnimation();
	statusElement.textContent = "Running C++ through WebAssembly...";
	isLoading = true;
	runButton.disabled = true;
	updateRunButton();

	const values = parseValues(valuesInput.value);
	valuesInput.value = values.join(", ");

	const module = await getSortingModule();
	const bytesPerInt = 4;
	const inputPointer = module._malloc(values.length * bytesPerInt);
	module.HEAP32.set(values, inputPointer / bytesPerInt);

	const jsonPointer = module._sort_trace_json_alloc(Number.parseInt(algorithmSelect.value, 10), inputPointer, values.length);
	const json = module.UTF8ToString(jsonPointer);
	module._free_string(jsonPointer);
	module._free(inputPointer);

	currentResult = JSON.parse(json);
	currentStep = 0;
	render();
	statusElement.textContent = "Animating trace";
	isLoading = false;
	runButton.disabled = false;
	startAnimation();
	updateRunButton();
}

function getFrame() {
	if (!currentResult) {
		const values = parseValues(valuesInput.value);
		return {
			state: values,
			event: null,
			total: 0
		};
	}

	if (currentStep === 0) {
		return {
			state: currentResult.input,
			event: null,
			total: currentResult.events.length
		};
	}

	return {
		state: currentResult.events[currentStep - 1].state,
		event: currentResult.events[currentStep - 1],
		total: currentResult.events.length
	};
}

function heightFor(value, values) {
	const min = Math.min(...values);
	const max = Math.max(...values);
	if (min === max) {
		return 60;
	}
	return 14 + ((value - min) / (max - min)) * 82;
}

function renderBars(values, event) {
	barsElement.innerHTML = "";

	values.forEach((value, index) => {
		const bar = document.createElement("div");
		bar.className = "bar";
		bar.style.setProperty("--height", String(heightFor(value, values)));
		bar.textContent = String(value);

		if (event) {
			const isFirst = event.first === index;
			const isSecond = event.second === index;
			if (event.type === "compare" && (isFirst || isSecond)) {
				bar.classList.add("is-compare");
			}
			if (event.type === "swap" && (isFirst || isSecond)) {
				bar.classList.add("is-swap");
			}
			if (event.type === "write" && isFirst) {
				bar.classList.add("is-write");
			}
			if (event.type === "done") {
				bar.classList.add("is-done");
			}
		}

		barsElement.appendChild(bar);
	});
}

function countEvents(type) {
	if (!currentResult) {
		return 0;
	}
	return currentResult.events.filter((event) => event.type === type).length;
}

function renderEvent(event) {
	if (!currentResult) {
		eventOutput.textContent = JSON.stringify({
			type: "ready",
			state: parseValues(valuesInput.value)
		}, null, 2);
		return;
	}

	if (!event) {
		eventOutput.textContent = JSON.stringify({
			type: "input",
			state: currentResult.input
		}, null, 2);
		return;
	}

	eventOutput.textContent = JSON.stringify(event, null, 2);
}

function render() {
	const frame = getFrame();
	const algorithmName = currentResult ? currentResult.algorithm : algorithmSelect.options[algorithmSelect.selectedIndex].textContent;

	activeAlgorithmElement.textContent = algorithmName;
	progressCurrentElement.textContent = String(currentStep);
	progressTotalElement.textContent = String(frame.total);
	comparisonsElement.textContent = String(countEvents("compare"));
	swapsElement.textContent = String(countEvents("swap"));
	writesElement.textContent = String(countEvents("write"));
	finalSizeElement.textContent = String(frame.state.length);
	renderBars(frame.state, frame.event);
	renderEvent(frame.event);
}

function stepForward() {
	if (!currentResult) {
		return;
	}
	currentStep = Math.min(currentStep + 1, currentResult.events.length);
	render();
	if (currentStep === currentResult.events.length) {
		stopAnimation();
		statusElement.textContent = "Sorted";
		updateRunButton();
	}
}

function animationDelay() {
	const speed = Number.parseInt(speedInput.value, 10);
	return 760 - speed * 70;
}

function startAnimation() {
	if (!currentResult || animationTimer) {
		return;
	}

	if (currentStep >= currentResult.events.length) {
		currentStep = 0;
		render();
	}

	animationTimer = window.setInterval(stepForward, animationDelay());
	statusElement.textContent = "Animating trace";
	updateRunButton();
}

function stopAnimation() {
	if (animationTimer) {
		window.clearInterval(animationTimer);
		animationTimer = null;
	}
}

function resetTraceToInput() {
	stopAnimation();
	currentResult = null;
	currentStep = 0;
	statusElement.textContent = "Input ready";
	render();
	updateRunButton();
}

function isComplete() {
	return currentResult && currentStep >= currentResult.events.length;
}

function updateRunButton() {
	if (isLoading) {
		runButton.textContent = "Running...";
		return;
	}

	if (animationTimer) {
		runButton.textContent = "Pause";
		return;
	}

	if (currentResult && !isComplete()) {
		runButton.textContent = "Resume";
		return;
	}

	runButton.textContent = "Run";
}

function handleRunButton() {
	if (isLoading) {
		return;
	}

	if (animationTimer) {
		stopAnimation();
		statusElement.textContent = "Paused";
		updateRunButton();
		return;
	}

	if (currentResult && !isComplete()) {
		startAnimation();
		return;
	}

	runSort().catch((error) => {
		isLoading = false;
		runButton.disabled = false;
		updateRunButton();
		statusElement.textContent = "WASM execution failed";
		eventOutput.textContent = String(error && error.stack ? error.stack : error);
	});
}

runButton.addEventListener("click", () => {
	handleRunButton();
});

shuffleButton.addEventListener("click", () => {
	valuesInput.value = buildRandomValues().join(", ");
	resetTraceToInput();
});

speedInput.addEventListener("input", () => {
	if (animationTimer) {
		stopAnimation();
		startAnimation();
	}
});

valuesInput.addEventListener("input", resetTraceToInput);

algorithmSelect.addEventListener("change", () => {
	resetTraceToInput();
});

getSortingModule()
	.then(() => {
		statusElement.textContent = "Ready";
		render();
		updateRunButton();
	})
	.catch((error) => {
		isLoading = false;
		updateRunButton();
		statusElement.textContent = "Failed to load WebAssembly";
		eventOutput.textContent = String(error && error.stack ? error.stack : error);
		render();
	});

render();
updateRunButton();
