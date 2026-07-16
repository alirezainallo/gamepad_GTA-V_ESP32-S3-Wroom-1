const keysContainer = document.getElementById("keys");

const editor = document.getElementById("editor");

const addButton = document.getElementById("addButton");
const closeButton = document.getElementById("closeButton");
const saveButton = document.getElementById("saveButton");
const deleteButton = document.getElementById("deleteButton");

const keyId = document.getElementById("keyId");
const keyName = document.getElementById("keyName");
const keyCommand = document.getElementById("keyCommand");
const tabBefore = document.getElementById("tabBefore");
const enterAfter = document.getElementById("enterAfter");

let keys = [];

let selectedKey = null;

let holdTimer = null;

const HOLD_TIME = 700;

async function api(url, method = "GET", body = null)
{
    const options =
    {
        method: method,
        headers:
        {
            "Content-Type": "application/json"
        }
    };

    if (body !== null)
        options.body = JSON.stringify(body);

    const response = await fetch(url, options);

    return await response.json();
}

async function loadKeys()
{
    keys = await api("/api/keys");

    renderKeys();
}

function renderKeys()
{
    keysContainer.innerHTML = "";

    keys.forEach(key =>
    {
        const button = document.createElement("div");

        button.className = "key";

        button.innerText = key.name;

        button.onmousedown = () =>
        {
            holdTimer = setTimeout(() =>
            {
                openEditor(key);

            }, HOLD_TIME);
        };

        button.onmouseup = () =>
        {
            if (holdTimer)
            {
                clearTimeout(holdTimer);

                executeKey(key.id);
            }
        };

        button.onmouseleave = () =>
        {
            clearTimeout(holdTimer);
        };

        button.ontouchstart = () =>
        {
            holdTimer = setTimeout(() =>
            {
                openEditor(key);

            }, HOLD_TIME);
        };

        button.ontouchend = () =>
        {
            if (holdTimer)
            {
                clearTimeout(holdTimer);

                executeKey(key.id);
            }
        };

        keysContainer.appendChild(button);
    });
}

async function executeKey(id)
{
    await api("/api/key", "POST",
    {
        id: id
    });
}

function openEditor(key)
{
    selectedKey = key;

    keyId.value = key.id;

    keyName.value = key.name;

    keyCommand.value = key.command;

    tabBefore.checked = key.tabBefore;

    enterAfter.checked = key.enterAfter;

    editor.classList.remove("hidden");
}

function closeEditor()
{
    selectedKey = null;

    editor.classList.add("hidden");
}

async function saveKey()
{
    const key =
    {
        id: Number(keyId.value),
        name: keyName.value.trim(),
        command: keyCommand.value.trim(),
        tabBefore: tabBefore.checked,
        enterAfter: enterAfter.checked
    };

    if (key.name.length === 0)
        return;

    if (key.command.length === 0)
        return;

    if (selectedKey == null)
    {
        await api("/api/key/add", "POST", key);
    }
    else
    {
        await api("/api/key/edit", "PUT", key);
    }

    closeEditor();

    await loadKeys();
}

async function deleteKey()
{
    if (selectedKey == null)
        return;

    await api("/api/key/delete", "DELETE",
    {
        id: selectedKey.id
    });

    closeEditor();

    await loadKeys();
}

function newKey()
{
    selectedKey = null;

    keyId.value = "";

    keyName.value = "";

    keyCommand.value = "";

    tabBefore.checked = false;

    enterAfter.checked = true;

    editor.classList.remove("hidden");
}

addButton.onclick = () =>
{
    newKey();
};

closeButton.onclick = () =>
{
    closeEditor();
};

saveButton.onclick = async () =>
{
    await saveKey();
};

deleteButton.onclick = async () =>
{
    await deleteKey();
};

editor.onclick = (e) =>
{
    if (e.target === editor)
    {
        closeEditor();
    }
};

window.addEventListener("keydown", (e) =>
{
    if (e.key === "Escape")
    {
        closeEditor();
    }
});

window.onload = async () =>
{
    await loadKeys();
};

