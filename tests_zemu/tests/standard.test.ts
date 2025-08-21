import Zemu, { zondaxMainmenuNavigation, ButtonKind, isTouchDevice } from '@zondax/zemu'
import  CreataApp  from 'ledger-creatachain-js'
import { defaultOptions, DEVICE_MODELS } from './common'

// @ts-ignore
// import secp256k1 from 'secp256k1/elliptic'

jest.setTimeout(90000)

// describe('Standard', function () {
//   test.concurrent.each(DEVICE_MODELS)('can start and stop container', async function (m) {
//     const sim = new Zemu(m.path)
//     try {
//       await sim.start({ ...defaultOptions, model: m.name })
//     } finally {
//       await sim.close()
//     }
//   })

//   test.concurrent.each(DEVICE_MODELS)('main menu', async function (m) {
//     const sim = new Zemu(m.path)
//     try {
//       await sim.start({ ...defaultOptions, model: m.name })
//       const nav = zondaxMainmenuNavigation(m.name, [1, 0, 0, 4, -5])
//       await sim.navigateAndCompareSnapshots('.', `${m.prefix.toLowerCase()}-mainmenu`, nav.schedule)
//     } finally {
//       await sim.close()
//     }
//   })

//   test.concurrent.each(DEVICE_MODELS)('get app version', async function (m) {
//     const sim = new Zemu(m.path)
//     try {
//       await sim.start({ ...defaultOptions, model: m.name })
//       const app = new CreataApp(sim.getTransport())
//       const resp = await app.getVersion()

//       console.log(resp)

//       expect(resp).toHaveProperty('major')
//       expect(resp).toHaveProperty('minor')
//       expect(resp).toHaveProperty('patch')
//     } finally {
//       await sim.close()
//     }
//   })

//   test.concurrent.each(DEVICE_MODELS)('get address', async function (m) {
//     const sim = new Zemu(m.path)
//     try {
//       await sim.start({ ...defaultOptions, model: m.name })
//       const app = new CreataApp(sim.getTransport())

//       // Derivation path. First 3 items are automatically hardened!
//       const path = "m/44'/118'/5'/0/3"
//       const resp = await app.getAddressAndPubKey(path, 'creata')

//       console.log(resp)

//       expect(resp).toHaveProperty('bech32_address')
//       expect(resp).toHaveProperty('compressed_pk')

//       expect(resp.bech32_address).toEqual('creata1wkd9tfm5pqvhhaxq77wv9tvjcsazuaykwsld65')
//       expect(resp.compressed_pk.length).toEqual(33)
//       expect(resp.compressed_pk.toString("hex")).toEqual('035c986b9ae5fbfb8e1e9c12c817f5ef8fdb821cdecaa407f1420ec4f8f1d766bf')
//     } finally {
//       await sim.close()
//     }
//   })

//   test.concurrent.each(DEVICE_MODELS)('show address', async function (m) {
//     const sim = new Zemu(m.path)
//     try {
//       await sim.start({
//         ...defaultOptions,
//         model: m.name,
//         approveKeyword: isTouchDevice(m.name) ? 'Confirm' : '',
//         approveAction: ButtonKind.DynamicTapButton,
//       })
//       const app = new CreataApp(sim.getTransport())

//       // Derivation path. First 3 items are automatically hardened!
//       const path = "m/44'/118'/5'/0/3"
//       const respRequest = app.showAddressAndPubKey(path, 'creata')
//       // Wait until we are not in the main menu
//       await sim.waitUntilScreenIsNot(sim.getMainMenuSnapshot())
//       await sim.compareSnapshotsAndApprove('.', `${m.prefix.toLowerCase()}-show_address`)

//       const resp = await respRequest
//       console.log(resp)

//       expect(resp).toHaveProperty('bech32_address')
//       expect(resp).toHaveProperty('compressed_pk')

//       expect(resp.bech32_address).toEqual('creata1wkd9tfm5pqvhhaxq77wv9tvjcsazuaykwsld65')
//       expect(resp.compressed_pk.length).toEqual(33)
//       expect(resp.compressed_pk.toString("hex")).toEqual('035c986b9ae5fbfb8e1e9c12c817f5ef8fdb821cdecaa407f1420ec4f8f1d766bf')
//     } finally {
//       await sim.close()
//     }
//   })

//   test.concurrent.each(DEVICE_MODELS)('show Eth address', async function (m) {
//     const sim = new Zemu(m.path)
//     try {
//       await sim.start({
//         ...defaultOptions,
//         model: m.name,
//         approveKeyword: isTouchDevice(m.name) ? 'Confirm' : '',
//         approveAction: ButtonKind.DynamicTapButton,
//       })
//       const app = new CreataApp(sim.getTransport())

//       // Derivation path. First 3 items are automatically hardened!
//       const path = "m/44'/60'/0'/0/1"
//       const hrp = 'inj'

//       // check with invalid HRP
//       const errorRespPk = app.getAddressAndPubKey(path, 'creata')
//       await expect(errorRespPk).rejects.toMatchObject({
//         returnCode: 0x698C,
//         errorMessage: 'Chain config not supported'
//       })

//       const respRequest = app.showAddressAndPubKey(path, hrp)
//       // Wait until we are not in the main menu
//       await sim.waitUntilScreenIsNot(sim.getMainMenuSnapshot())
//       await sim.compareSnapshotsAndApprove('.', `${m.prefix.toLowerCase()}-show_eth_address`)

//       const resp = await respRequest
//       console.log(resp)

//       expect(resp).toHaveProperty('bech32_address')
//       expect(resp).toHaveProperty('compressed_pk')

//       expect(resp.compressed_pk.length).toEqual(33)

//       // Verify address
//       const secp256k1 = require("secp256k1");
//       const keccak = require("keccak256");
//       const { bech32 } = require("bech32");

//       // Take the compressed pubkey and verify that the expected address can be computed
//       const uncompressPubKeyUint8Array = secp256k1.publicKeyConvert(resp.compressed_pk, false).subarray(1);
//       const ethereumAddressBuffer = Buffer.from(keccak(Buffer.from(uncompressPubKeyUint8Array))).subarray(-20);
//       const eth_address = bech32.encode(hrp, bech32.toWords(ethereumAddressBuffer)); // "creata15n2h0lzvfgc8x4fm6fdya89n78x6ee2fm7fxr3"

//       expect(resp.bech32_address).toEqual(eth_address)
//       expect(resp.bech32_address).toEqual('inj15n2h0lzvfgc8x4fm6fdya89n78x6ee2f3h7z3f')
//     } finally {
//       await sim.close()
//     }
//   })

//   test.concurrent.each(DEVICE_MODELS)('show address HUGE', async function (m) {
//     const sim = new Zemu(m.path)
//     try {
//       await sim.start({
//         ...defaultOptions,
//         model: m.name,
//         approveKeyword: isTouchDevice(m.name) ? 'Confirm' : '',
//         approveAction: ButtonKind.DynamicTapButton,
//       })
//       const app = new CreataApp(sim.getTransport())

//       // Derivation path. First 3 items are automatically hardened!
//       const path = "m/44'/118'/2147483647'/0/4294967295"
//       const resp = app.showAddressAndPubKey(path, 'creata')
//       console.log(resp)

//       await expect(resp).rejects.toMatchObject({
//         returnCode: 0x6989,
//         errorMessage: 'Invalid HD Path Value. Expert Mode required.'
//       })
//     } finally {
//       await sim.close()
//     }
//   })

//   test.concurrent.each(DEVICE_MODELS)('show address HUGE Expert', async function (m) {
//     const sim = new Zemu(m.path)
//     try {
//       await sim.start({
//         ...defaultOptions,
//         model: m.name,
//         approveKeyword: isTouchDevice(m.name) ? 'Confirm' : '',
//         approveAction: ButtonKind.DynamicTapButton,
//       })
//       const app = new CreataApp(sim.getTransport())

//       // Activate expert mode
//       await sim.toggleExpertMode();

//       // Derivation path. First 3 items are automatically hardened!
//       const path = "m/44'/118'/2147483647'/0/4294967295"
//       const respRequest = app.showAddressAndPubKey(path, 'creata')

//       // Wait until we are not in the main menu
//       await sim.waitUntilScreenIsNot(sim.getMainMenuSnapshot())
//       await sim.compareSnapshotsAndApprove('.', `${m.prefix.toLowerCase()}-show_address_huge`)

//       const resp = await respRequest
//       console.log(resp)

//       expect(resp).toHaveProperty('bech32_address')
//       expect(resp).toHaveProperty('compressed_pk')

//       expect(resp.bech32_address).toEqual('creata1ex7gkwwmq4vcgdwcalaq3t20pgwr37u6ntkqzh')
//       expect(resp.compressed_pk.length).toEqual(33)
//     } finally {
//       await sim.close()
//     }
//   })
// })
